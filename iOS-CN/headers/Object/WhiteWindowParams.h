//
//  WhiteWindowParams.h
//  Whiteboard
//
//  Created by yleaf on 2022/2/9.
//

#import "WhiteObject.h"

NS_ASSUME_NONNULL_BEGIN


typedef NSString * WhitePrefersColorScheme NS_STRING_ENUM;
/** `WhitePrefersColorSchemeAuto` 仅适用于 iOS 13 及以上的设备。*/
FOUNDATION_EXPORT WhitePrefersColorScheme const WhitePrefersColorSchemeAuto;
FOUNDATION_EXPORT WhitePrefersColorScheme const WhitePrefersColorSchemeLight;
FOUNDATION_EXPORT WhitePrefersColorScheme const WhitePrefersColorSchemeDark;

/** 白板窗口参数。*/
@interface WhiteWindowParams : WhiteObject

// /** 各个端本地显示多窗口内容时，高与宽比例，默认为 9:16。该值应该各个端保持统一，否则会有不可预见的情况。 */
// @property (nonatomic, strong) NSNumber *containerSizeRatio;
// /** 多窗口区域（主窗口）以外的空间显示 PS 棋盘背景，默认值为 `YES`。*/
// @property (nonatomic, assign) BOOL chessboard;
/** 是否开启窗口最大化，开启后添加的窗口将全屏展示。 默认值为 `NO`。*/
@property (nonatomic, assign) BOOL fullscreen;
// /** 驼峰形式的 CSS，透传给多窗口时，最小化 div 的 css */
// @property (nonatomic, copy, nullable) NSDictionary *collectorStyles;
// /** 是否在网页控制台打印日志，默认 YES */
// @property (nonatomic, assign) BOOL debug;
// /** 暗黑模式, 本地效果， 不会同步到远端， 默认Light, 设置auto只有在iOS13以上才会生效*/
// @property (nonatomic, copy) WhitePrefersColorScheme prefersColorScheme;
/** 使用 CSS 覆盖白板窗口样式。 */
@property (nonatomic, copy) NSString *overwriteStyles;

@end

NS_ASSUME_NONNULL_END
