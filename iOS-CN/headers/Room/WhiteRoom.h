//
//  WhiteRoom.h
//  dsBridge
//
//  Created by leavesster on 2018/8/11.
//

#import <Foundation/Foundation.h>
#import "WhiteGlobalState.h"
#import "WhiteMemberState.h"
#import "WhiteImageInformation.h"
#import "WhitePptPage.h"
#import "WhiteRoomMember.h"
#import "WhiteBroadcastState.h"
#import "WhiteRoomCallbacks.h"
#import "WhiteRoomState.h"
#import "WhiteEvent.h"
#import "WhiteScene.h"
#import "WhiteSceneState.h"
#import "WhitePanEvent.h"
#import "WhiteDisplayer.h"
#import "WhiteSDK+Room.h"
#import "WhiteWindowDocsEventOptions.h"

@class WhiteBoardView;

NS_ASSUME_NONNULL_BEGIN

/** 用于操作互动白板实时房间。 */
@interface WhiteRoom : WhiteDisplayer

#pragma mark - 同步 API
/** 用户在当前房间中的用户 ID。与该用户在 [WhiteRoomMember](WhiteRoomMember) 中的 `memberId` 相同。
 */
@property (nonatomic, strong, readonly) NSNumber *observerId;
/** 房间 UUID，即房间唯一标识符。 */
@property (nonatomic, copy, readonly) NSString *uuid;
/** 房间的全局状态。详见 [WhiteGlobalState](WhiteGlobalState)。*/
@property (nonatomic, strong, readonly) WhiteGlobalState *globalState;
/** 工具信息。详见 [WhiteReadonlyMemberState](WhiteReadonlyMemberState)。 */
@property (nonatomic, strong, readonly) WhiteReadonlyMemberState *memberState;
/** 在线成员信息。详见 [WhiteRoomMember](WhiteRoomMember)。 */
@property (nonatomic, strong, readonly) NSArray<WhiteRoomMember *> *roomMembers;
/** 用户视角状态信息， 包括用户当前场景状态、主播信息。详见 [WhiteBroadcastState](WhiteBroadcastState)。 */
@property (nonatomic, strong, readonly) WhiteBroadcastState *broadcastState;
/** 视角缩放比例。 */
@property (nonatomic, assign, readonly) CGFloat scale;
/** 房间状态信息，详见 [WhiteDisplayerState](WhiteDisplayerState)。*/
@property (nonatomic, strong, readonly) WhiteRoomState *state;
/** 白板页面（场景）状态。详见 [WhiteSceneState](WhiteSceneState)。 */
@property (nonatomic, strong, readonly) WhiteSceneState *sceneState;
/** 房间连接状态。详见 [WhiteRoomPhase](WhiteRoomPhase)。 */
@property (nonatomic, assign, readonly) WhiteRoomPhase phase;

#pragma mark - Apple Pencil

/**
 设置是否只允许用户使用 Apple Pencil 在白板上绘制和书写。

 设置 `setDrawOnlyApplePencil(YES)` 后，用户只能使用 Apple Pencil 在白板上绘制和书写，无法使用手指绘制和书写。
 如果用户用手指触碰白板，SDK 会触发两个 [fireRoomStateChanged]([WhiteRoomCallbackDelegate fireRoomStateChanged:]) 回调，报告当前使用的白板工具 (`memberState`) 在 `ApplianceClicker` 和 `AppliancePencil` 之间发生了切换。

 **Note:**

 - 该属性仅在 iPad 设备上生效。
 - 该属性的设置建议跟随 `UIPencilInteraction.prefersPencilOnlyDrawing` 的设置。

 @param drawOnlyPencil 是否只允许用户使用 Apple Pencil 绘制和书写：

 - `YES`：只允许使用 Apple Pencil 在白板上绘制和书写。
 - `NO`：（默认）允许使用 Apple Pencil 或手指在白板上绘制和书写。
 */
- (void)setDrawOnlyApplePencil:(BOOL)drawOnlyPencil;

#pragma mark - Set API

/**
 修改互动白板实时房间的公共全局状态。

 实时房间的 `globalState` 属性为公共全局变量，房间内所有用户看到的都是相同的 `globalState`，所有互动模式用户都可以读写。修改 `globalState` 属性会立即生效并同步给所有用户。

 1.0 迁移用户，请阅读文档站中 [页面（场景）管理] ，使用 `setScencePath`。

 @param globalState 房间公共全局状态，自定义字段。详见 [WhiteGlobalState](WhiteGlobalState)。
 */
- (void)setGlobalState:(WhiteGlobalState * )globalState;

/**
 修改房间内的工具状态。

 调用该方法会立刻更新房间的 [WhiteMemberState](WhiteMemberState)。

 你可以调用 [getMemberStateWithResult]([WhiteRoom getMemberStateWithResult:])  获取最新设置的工具状态。

 @param modifyState 需要修改的工具状态，详见 [WhiteMemberState](WhiteMemberState)。
 */
- (void)setMemberState:(WhiteMemberState *)modifyState;

/**
 切换视角模式。

 互动白板实时房间支持对用户设置以下视角模式：

 - `Broadcaster`: 主播模式。该模式下用户可以主动调整视角，并将自己的视角同步给房间内所有其他用户。
 - `Follower`：跟随模式。该模式下用户的视角会跟随主播的视角。
 - `Freedom`：（默认）自由模式。该模式下用户可以主动调整视角，不受其他用户视角模式设置的影响，也不会影响其他用户的视角模式设置。

 该方法的设置会影响房间内所有用户的视角模式：

 - 当房间内不存在主播模式的用户时，所有用户的视角都默认为自由模式。
 - 当一个用户的视角设置为主播模式后，房间内其他所有用户（包括新加入房间的用户）的视角会被自动设置为跟随模式。
 - 当跟随模式的用户进行白板操作时，其视角会自动切换为自由模式。你可以调用 [disableOperations]([WhiteRoom disableOperations:]) 禁止跟随模式的用户操作白板，以保证其保持跟随模式。

 @param viewMode 视角模式。

 */
- (void)setViewMode:(WhiteViewMode)viewMode;


#pragma mark - Action API

/** 获取 debug 信息。

 @param completionHandler 方法调用结果：

 - 如果方法调用成功，则返回调试日志信息。
 - 如果方法调用失败，则返回错误信息。
 */
- (void)debugInfo:(void (^ _Nullable)(NSDictionary * _Nullable dict))completionHandler;


//- (void)refreshViewSize;

/**
 主动断开与互动白板实时房间的连接。

 该方法会把与当前房间对象相关的所有资源释放掉。如果要再次加入房间，需要重新调用 [joinRoomWithConfig]([WhiteSDK joinRoomWithConfig:callbacks:completionHandler:])。

 @param completeHandler 调用结果：

 - 如果方法调用成功，则返回房间的全局状态。
 - 如果方法调用失败，则返回错误信息。
 */
- (void)disconnect:(void (^ _Nullable) (void))completeHandler;

/** 用户是否主动断开与白板房间的连接。在调用 [disconnect]([WhiteRoom disconnect:]) 主动断连时，该值会被立即赋值为 `YES`。 */
@property (nonatomic, assign, readonly) BOOL disconnectedBySelf;

/**
 设置用户在房间中是否为互动模式。
 在加入房间前，就可以在 [WhiteRoomConfig](WhiteRoomConfig) 中设置 [isWritable]([WhiteRoomConfig isWritable]) ，来决定该模式。

 @param writable 用户在房间中是否为互动模式：

  - `YES`：互动模式，即具有读写权限。
  - `NO`：订阅模式，即具有只读权限。

 @param completionHandler 方法调用结果：

 - 如果方法调用成功，则返回用户在房间中的读写状态。
 - 如果方法调用失败，则返回错误信息。
 */
- (void)setWritable:(BOOL)writable completionHandler:(void (^ _Nullable)(BOOL isWritable, NSError * _Nullable error))completionHandler;
/**
 本地用户在当前互动白板实时房间是否为互动模式。

 - `YES`：互动模式，即具有读写权限。
 - `NO`：订阅模式，即具有只读权限。
 */
@property (nonatomic, assign, readonly, getter=isWritable) BOOL writable;


/**
 禁止/允许用户调整（移动或缩放）视角。

 @param disableCameraTransform 是否禁止用户调整视角：

  - `YES`：禁止用户调整视角。
  - `NO`：（默认）允许用户调整视角。
 */
- (void)disableCameraTransform:(BOOL)disableCameraTransform;

/**
 禁止/允许用户操作工具。

 @param disable 是否禁止用户操作工具：

  - `YES`：禁止用户操作工具操作。
  - `NO`：（默认）允许用户操作工具输入操作。
 */
- (void)disableDeviceInputs:(BOOL)disable;

/**
 发送自定义事件。

 @param eventName 自定义事件名称，详见 [WhiteEvent](WhiteEvent)。

 @param payload 自定义事件内容，详见 [WhiteEvent](WhiteEvent)。
 */
- (void)dispatchMagixEvent:(NSString *)eventName payload:(NSDictionary *)payload;

#pragma mark - PPT

/**
 播放动态 PPT 下一页。

 当前 PPT 页面的动画已全部执行完成时，SDK 会将场景切换至下一页 PPT。
 */
- (void)pptNextStep;

/**
 返回动态 PPT 上一页。

 当前 PPT 页面的动画全部回退完成时，SDK 会将场景切回至上一页 PPT。
 */
- (void)pptPreviousStep;

#pragma mark - Text API

/**
 在指定位置插入文字。

 @param x 第一个文字左侧边的中点在世界坐标系中的 X 轴坐标。
 @param y 第一个文字左侧边的中点在世界坐标系中的 Y 轴坐标。
 @param textContent 初始的文字内容，不传则为空。
 @param completionHandler 方法调用结果：

 - 如果方法调用成功，则返回文字的标识符。
 - 如果方法调用失败，则返回错误信息。
 */
- (void)insertText:(CGFloat)x y:(CGFloat)y textContent:(NSString *)textContent completionHandler:(void (^) (NSString * textId))completionHandler;

/**
 * 更新指定文本的内容。
 * @param textId 文字标识符。
 * @param textContent 文字内容。
 */
- (void)updateText:(NSString *)textId textContent:(NSString *)textContent;


#pragma mark - Image API

/**
 插入图片显示区域。

 SDK 会根据你传入的 `imageInfo` 在白板上设置并插入图片的显示区域。

 **Note:**

 你也可以调用 [insertImage]([WhiteRoom insertImage:src:]) 方法同时传入图片信息和图片的 URL 地址，在白板中插入并展示图片。

 @param imageInfo 图片信息，详见 [WhiteImageInformation](WhiteImageInformation)。
 @param src 图片 URL 地址，详见 [WhiteImageInformation](WhiteImageInformation)。
 */
- (void)insertImage:(WhiteImageInformation *)imageInfo src:(NSString *)src;

/**
 插入图片显示区域。

 SDK 会根据你传入的 `imageInfo` 在白板上设置并插入图片的显示区域。

 @param imageInfo 图片信息，详见 [WhiteImageInformation](WhiteImageInformation)。
 */
- (void)insertImage:(WhiteImageInformation *)imageInfo;

/**
 展示图片。

 该方法可以将指定的网络图片展示到指定的图片显示区域。

 **Note:**

 调用该方法前，请确保你已经调用 [insertImage]([WhiteRoom insertImage:src:]) 方法在白板上插入了图片的显示区域。

 @param uuid 图片显示区域的 UUID, 即在 [insertImage]([WhiteRoom insertImage:src:]) 方法的 `imageInfo` 中传入的图片 UUID。
 @param src 图片的 URL 地址。必须确保 app 客户端能访问该 URL，否则无法正常展示图片。
 */
- (void)completeImageUploadWithUuid:(NSString *)uuid src:(NSString *)src;

/**
 关闭/开启橡皮擦擦除图片功能。

 @param disable 是否关闭橡皮擦擦除图片功能：

 - `YES`：禁止橡皮擦擦除图片。
 - `NO`：（默认）允许橡皮擦擦除图片。
 */
- (void)disableEraseImage:(BOOL)disable;

#pragma mark - 延时

/** 设置本地显示远端白板内容的 Unix 时间戳。

 @since 2.12.24

 调用该方法后，SDK 会根据你设置的 `timestamp` 的值显示接收到的远端白板内容。

 在同时订阅音视频流和白板内容的场景中，你可以从音视频流附带的 SEI 帧中获取时间信息，并调用该方法设置远端白板内容在本地的显示时间，以确保音视频流和白板内容实时同步。

 @param timestamp 远端白板内容在本地显示的 Unix 时间戳，单位为秒。
 */
- (void)syncBlockTimestamp:(NSTimeInterval)timestamp;

/**
 设置本地显示远端白板内容的延时。

 设置该参数后，当本地用户接收到远端白板内容后，SDK 会根据你设置的 `delay` 的值延迟显示白板内容。

 在音视频传输延时较大的场景中，如使用 CDN 推送音视频流时，你可以使用该参数延迟显示接收到的远端白板内容，以确保白板内容与音视频同步。

 @param delay 延时时长，单位为秒，默认值为 0，取值大于等于 0。
 */
- (void)setTimeDelay:(NSTimeInterval)delay;

/**
 本地显示远端白板内容的延时，单位为秒，默认值为 0。取值大于等于 0。
 */
@property (nonatomic, assign, readonly) NSTimeInterval delay;

@end


#pragma mark - 页面（场景）管理 API

@interface WhiteRoom (Scene)


/**
 获取房间当前场景目录下的场景状态。

 @param result 回调。返回当前场景目录下的场景状态，详见 [WhiteSceneState](WhiteSceneState)。
 */
- (void)getSceneStateWithResult:(void (^) (WhiteSceneState *state))result;

/**
 获取房间当前场景目录下的场景列表。

 @param result 回调。返回当前场景目录下的场景列表，详见 [WhiteScene](WhiteScene)。
 */
- (void)getScenesWithResult:(void (^) (NSArray<WhiteScene *> *scenes))result;

/**
 切换至指定的场景。

 方法调用成功后，房间内的所有用户看到的白板都会切换到指定场景。

 **Note:**

  - 该方法为同步调用。
  - 调用 `setScenePath` 方法修改或新增场景后，无法通过 [setScenePath]([WhiteRoom setScenePath:]) 立即获取最新的场景状态。此时，如果需要立即获取最新的场景状态，可以调用 [setScenePath:completionHandler:]([WhiteRoom setScenePath:completionHandler:])。

 场景切换失败可能有以下原因：

 - 路径不合法，请确保场景路径以 "/"，由场景目录和场景名构成。
 - 场景路径对应的场景不存在。
 - 传入的路径是场景目录的路径，而不是场景路径。
 @param path 想要切换到的场景的场景路径，请确保场景路径以 "/"，由场景目录和场景名构成，例如，`/math/classA`。
 */

- (void)setScenePath:(NSString *)path;
/**
 切换至指定的场景。

 方法调用成功后，房间内的所有用户看到的白板都会切换到指定场景。

 **Note:**

 - 该方法为异步调用。
 - 调用 `setScenePath` 方法修改或新增场景后，你可以通过 [getSceneStateWithResult:](getSceneStateWithResult:) 立即获取最新的场景状态。
 - 场景切换失败可能有以下原因：
  - 路径不合法，请确保场景路径以 "/"，由场景目录和场景名构成。
  - 场景路径对应的场景不存在。
  - 传入的路径是场景目录的路径，而不是场景路径。
 @param dirOrPath    想要切换到的场景的场景路径，请确保场景路径以 "/"，由场景目录和场景名构成，例如，`/math/classA`.
 @param completionHandler 方法调用结果：

 - 如果方法调用成功，则返回 `YES`.
 - 如果方法调用失败，则返回错误信息。
 */
- (void)setScenePath:(NSString *)dirOrPath completionHandler:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))completionHandler;


/**
 切换至当前场景目录下的指定场景。

 方法调用成功后，房间内的所有用户看到的白板都会切换到指定场景。

 **Note:**

 指定的场景必须在当前场景目录中，否则，方法调用会失败。

 @param index   目标场景在当前场景目录下的索引号。
 @param completionHandler 方法调用结果：

 - 如果方法调用成功，则返回 `YES`.
 - 如果方法调用失败，则返回错误信息。
 */
- (void)setSceneIndex:(NSUInteger)index completionHandler:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))completionHandler;

/**
 在指定场景目录下插入多个场景。

 **Note:**

 调用该方法插入多个场景后不会切换到新插入的场景。如果要切换至新插入的场景，需要调用 [setScenePath]([WhiteRoom setScenePath:])。

 @param dir    场景目录名称，必须以 `/` 开头。不能为场景路径。
 @param scenes 由多个场景构成的数组。单个场景的字段详见 [WhiteScene](WhiteScene)。
 @param index  待插入的多个场景中，第一个场景在该场景目录的索引号。如果传入的索引号大于该场景目录已有场景总数，新插入的场景会排在现有场景的最后。场景的索引号从 0 开始。
 */
- (void)putScenes:(NSString *)dir scenes:(NSArray<WhiteScene *> *)scenes index:(NSUInteger)index;

/**
 清除当前场景的所有内容。

 @param retainPPT 是否保留 PPT 内容：

  - `YES`：保留 PPT。
  - `NO`：连 PPT 一起清空。
 */
- (void)cleanScene:(BOOL)retainPPT;

/**
 删除场景或者场景目录。
 @param dirOrPath 场景目录路径或者场景路径。如果传入的是场景目录，则会删除该场景目录下的所有场景。

 **Note:**

 - 互动白板实时房间内必须至少有一个场景。当删除所有的场景后，SDK 会自动生成一个路径为 `/init` 初始场景（房间初始化时的默认场景）。
 - 如果删除白板当前所在场景，白板会展示被删除场景所在场景目录的最后一个场景
 - 如果删除的是场景目录，则该场景目录下的所有场景都会被删除。
 - 如果删除的是当前场景所在的场景目录，例如 `dirA`，SDK 会执行向上递归逻辑选择新的场景作为当前场景，规则如下：
    - 如果当前场景目录路径下还有其他场景目录，例如 `dirB`，排在被删除的场景目录 `dirA` 后面，则将场景切换至
    `dirB` 中的第一个场景（index 为 0）。
    - 如果当前场景目录路径下 `dirA` 后不存在场景目录，则查看当前场景目录路径下是否存在场景；
    如果存在，则将场景切换至当前场景目录路径下的第一个场景（index 为 0）。
    - 如果当前场景目录路径下 `dirA` 后没有场景目录，也不存在任何场景，则查看 `dirA` 前面是否存在场景目录 `dirC`；如果存在，则选择 `dirC` 中的第一个场景（index 为 0）。
    - 以上都不满足，则继续向上递归执行该逻辑。
 */
- (void)removeScenes:(NSString *)dirOrPath;

/**
 移动场景。

 成功移动场景后，场景路径也会改变。

 **Note:**

 - 该方法只能移动场景，不能移动场景目录，即 `source` 只能是场景路径，不能是场景目录路径。
 - 该方法支持改变指定场景在当前所属场景目录下的位置，也支持将指定场景移至其他场景目录。
 @param source 需要移动的场景原路径。必须为场景路径，不能是场景目录的路径。
 @param target 目标场景目录的路径或目标场景的路径：

  - 当 `target` 设置为场景目录时，表示将指定场景移至其他场景目录中，场景路径会发生改变，但是场景名称不变。
  - 当 `target` 设置为场景时，表示改变指定场景在当前场景目录的位置，场景路径和场景名都会发生改变。
 */
- (void)moveScene:(NSString *)source target:(NSString *)target;


/**
 * 以下方法可以对使用【选择框】的工具进行操作。
 */
#pragma mark - 执行操作 API

/**
 复制选中内容。

 该方法会将选中的内容存储到内存中，不会粘贴到白板中。

 **Note:**

 该方法仅当 [disableSerialization]([WhiteRoom disableSerialization:]) 设为 `NO` 时生效。
 */
- (void)copy;

/**
 粘贴复制的内容。

 该方法会将 [copy]([WhiteRoom copy]) 方法复制的内容粘贴到白板中（用户当前的视角中间）。

 **Note:**

 - 该方法仅当 [disableSerialization]([WhiteRoom disableSerialization:]) 设为 `NO` 时生效。
 - 多次调用该方法时，不能保证粘贴的内容每次都在用户当前的视角中间，可能会出现随机偏移。
 */
- (void)paste;

/**
 复制并粘贴选中的内容。

 该方法会将选中的内容复制并粘贴到白板中（用户当前的视角中间）。

 **Note:**

 - 该方法仅当 [disableSerialization]([WhiteRoom disableSerialization:]) 设为 `NO` 时生效。
 - 多次调用该方法时，不能保证粘贴的内容每次都在用户当前的视角中间，可能会出现随机偏移。
 */
- (void)duplicate;


- (void)deleteOpertion DEPRECATED_MSG_ATTRIBUTE("use deleteOperation");

/**
 * 删除选中内容。
 */
- (void)deleteOperation;

/**
 开启/禁止本地序列化。

 设置 `disableSerialization(true)` 后，以下方法将不生效：

 - [redo]([WhiteRoom redo])
 - [undo]([WhiteRoom undo])
 - [duplicate]([WhiteRoom duplicate])
 - [copy]([WhiteRoom copy])
 - [paste]([WhiteRoom paste])

 **Warning:**

 如果要设置 `disableSerialization(false)`，必须确保同一房间内所有用户使用的 SDK 满足以下版本要求，否则会导致 app 客户端崩溃。

 - Web SDK 2.9.2 或之后版本
 - Android SDK 2.9.3 或之后版本
 - iOS SDK 2.9.3 或之后版本

 @param disable 是否禁止本地序列化：

 - `YES`：（默认）禁止开启本地序列化；
 - `NO`： 开启本地序列化，即可以对本地操作进行解析。
 */
- (void)disableSerialization:(BOOL)disable;

/**
 重做，即回退撤销操作。

 **Note:**

 该方法仅当 [disableSerialization]([WhiteRoom disableSerialization:]) 设为 `NO` 时生效。
 */
- (void)redo;

/**
 撤销上一步操作。

 **Note:**

 该方法仅当 [disableSerialization]([WhiteRoom disableSerialization:]) 设为 `NO` 时生效。
 */
- (void)undo;

@end

#pragma mark - 异步 API

@interface WhiteRoom (Asynchronous)

/**
 获取房间的全局状态。

 **Note:**

 - 该方法为异步调用。
 - 通过 [setCustomGlobalStateClass]([WhiteDisplayerState setCustomGlobalStateClass:]) 设置自定义状态后，如需异步获取，可以通过 `getRoomStateWithResult` 获取自定义的当前房间状态。
 - 调用 [setGlobalState]([WhiteRoom setGlobalState:]) 方法后，可以立刻调用该方法。
 @param result 回调。返回房间的全局状态，详见 [WhiteGlobalState](WhiteGlobalState)。
 */
- (void)getGlobalStateWithResult:(void (^) (WhiteGlobalState *state))result;
/**
 获取当前的工具状态。

 **Note:**

 该方法为异步调用。调用 [setMemberState](setMemberState:) 方法后，可以立刻调用该方法。

 @param result 回调。返回当前的工具状态，详见 [WhiteMemberState](WhiteMemberState) 。
 */
- (void)getMemberStateWithResult:(void (^) (WhiteMemberState *state))result;
/**
 获取实时房间用户列表。

 **Note:**

 - 该方法为异步调用。
 - 房间的用户列表仅包含互动模式（具有读写权限）的用户，不包含订阅模式（只读权限）的用户。

 @param result 回调。返回当前房间的用户列表，详见 [WhiteRoomMember](WhiteRoomMember)。
 */
- (void)getRoomMembersWithResult:(void (^) (NSArray<WhiteRoomMember *> *roomMembers))result;
/**
 获取用户视角状态。

 **Note:**

 该方法为异步调用。

 @param result 回调。返回当前用户视角状态，详见 [WhiteBroadcastState](WhiteBroadcastState)。
 */
- (void)getBroadcastStateWithResult:(void (^) (WhiteBroadcastState *state))result;
/**
 获取房间连接状态。

 **Note:**

 该方法为异步调用。

 @param result 回调。返回当前房间连接状态，详见 [WhiteRoomPhase](WhiteRoomPhase)。
 */
- (void)getRoomPhaseWithResult:(void (^) (WhiteRoomPhase phase))result;
/**
 获取用户当前的视角缩放比例。该方法为异步调用。

 @param result 回调。返回当前视角缩放比例。
 */
- (void)getZoomScaleWithResult:(void (^) (CGFloat scale))result;
/**
 获取当前房间状态。

 **Note:**

 该方法为异步调用。

 @param result 回调。返回当前房间状态，详见 [WhiteRoomState](WhiteRoomState)。
 */
- (void)getRoomStateWithResult:(void (^) (WhiteRoomState *state))result;

@end

@interface WhiteRoom(MainView)

/**
 * 插入小窗应用。
 * 
 * 多窗口模式下，PPT 或自定义插件等可以作为小窗应用插入白板，在一个新的窗口中展示。
 * 
 * @param appParams 小窗应用属性，详见 [WhiteAppParam](WhiteAppParam)。
 * @param completionHandler 方法调用结果：
 * 
 * - 如果方法调用成功，则返回 `appId`，即小窗应用 ID。
 * - 如果方法调用失败，则返回错误信息。
 *
 * @note 多次插入同一个小窗应用返回的 `appId` 为 `nil`，表示插入失败。
 */
- (void)addApp:(WhiteAppParam *)appParams completionHandler:(void (^)(NSString *appId))completionHandler;

/**
 * 关闭指定小窗应用的窗口。
 * 
 * 该方法仅在多窗口模式下有效, 无论应用 ID 是否有效都会触发回调。
 *
 * @param appId 小窗应用 ID。
 * @param completionHandler 方法调用结果：
 * 
 * - 如果方法调用成功，则窗口关闭。
 * - 如果方法调用失败，则返回错误信息。
 */
- (void)closeApp:(NSString *)appId completionHandler:(void (^)(void))completionHandler;

/**
 * 切换聚焦窗口为指定小窗应用的窗口。
 * 
 * 该方法仅在多窗口模式下有效。
 *
 * @param appId 小窗应用 ID。
 */
- (void)focusApp:(NSString *)appId;

/** 查询所有小窗应用的信息。
 * 
 *  该方法仅在多窗口下有效。
 * 
 * @param completionHandler 查询结果回调。
  * 
 * - 如果方法调用成功，则返回一个以应用 ID 为键，包含所有小窗应用信息的字典。详见 [WhiteAppSyncAttributes](WhiteAppSyncAttributes)。
 * - 如果方法调用失败，则返回错误信息。
 *
*/
- (void)queryAllAppsWithCompletionHandler:(void (^)(NSDictionary<NSString *, WhiteAppSyncAttributes *> *apps, NSError * _Nullable error))completionHandler;

/** 查询指定小窗应用的信息。
 * 
 *  该方法仅在多窗口下有效。
 * 
 * @param appId 小窗应用 ID。
 * @param completionHandler 查询结果回调。
 * 
 * - 如果方法调用成功，则返回小窗应用相关信息，详见 [WhiteAppSyncAttributes](WhiteAppSyncAttributes)。
 * - 如果方法调用失败，则返回错误信息。
 *
 */
- (void)queryApp:(NSString *)appId completionHandler:(void (^)(WhiteAppSyncAttributes *appParam, NSError * _Nullable error))completionHandler;


/**
 * 发送文档操作事件。
 * 在多窗口模式下，该方法可以用来操作当前聚焦的文档窗口。
 *
 * @param docsEvent 事件类型。详见 [WhiteWindowDocsEventKey](WhiteWindowDocsEventKey)。
 * @param options 可选事件参数。该参数仅在设置 `docsEvent` 为 `WhiteWindowDocsEventJumpToPage` 时有效，用于传入跳转的页码。详见 [WhiteWindowDocsEventOptions](WhiteWindowDocsEventOptions)。
 * @param completionHandler 方法调用结果。
 *
 * @warning 该方法只有在文档视图加载完毕时才能调用。不支持多次连续调用，只有当前的转场动画播放完毕之后才能进行下一次调用。
 */
- (void)dispatchDocsEvent:(WhiteWindowDocsEventKey)docsEvent options:( WhiteWindowDocsEventOptions * _Nullable )options completionHandler:(void (^)(bool success))completionHandler;

@end

#pragma mark - 弃用方法
@interface WhiteRoom (Deprecated)

/**
 该方法已废弃，请使用 [disableDeviceInputs]([WhiteRoom disableDeviceInputs:]) 和 [disableCameraTransform]([WhiteDisplayer disableCameraTransform:])。

 禁止操作。
 @param disable 是否禁止操作，`true` 为禁止。
 */
- (void)disableOperations:(BOOL)disable DEPRECATED_MSG_ATTRIBUTE("use disableDeviceInputs and disableCameraTransform");

/**
 该方法已废弃，请使用 [moveCamera]([WhiteDisplayer moveCamera:])。

 缩小放大白板。
 @param scale 相对于原始大小的比例。
 */
- (void)zoomChange:(CGFloat)scale DEPRECATED_MSG_ATTRIBUTE("use moveCamera:");

/**
 该方法已废弃，请使用 [getScenesWithResult]([WhiteRoom getScenesWithResult:])。

 获取所有 ppt 图片。
 @param result 回调。返回所有 ppt 图片的地址。
 */
- (void)getPptImagesWithResult:(void (^) (NSArray<NSString *> *pptPages))result DEPRECATED_MSG_ATTRIBUTE("use getScenesWithResult:");

@end

NS_ASSUME_NONNULL_END
