//
//  WhiteSDK.h
//  Pods-white-ios-sdk_Example
//
//  Created by leavesster on 2018/8/11.
//

#import <Foundation/Foundation.h>
#import "WhiteBoardView.h"
#import "WhiteCommonCallbacks.h"
#import "WhiteSdkConfiguration.h"
#import "WhiteAudioMixerBridge.h"
#import "WhiteFontFace.h"
NS_ASSUME_NONNULL_BEGIN

/** The `WhiteSDK` class. */
@interface WhiteSDK : NSObject


/** The version of the current SDK in the string format. For example, `"2.12.11"`. */
+ (NSString *)version;

/**
 Sets RTC audio mixing and event callbacks and initializes the `WhiteSDK` object.

 **Note:**

 Ensure that you call `WhiteSdk` to initialize a `WhiteSdk` object before calling any other APIs.
 @param boardView     The whiteboard view. See [WhiteBoardView](WhiteBoardView).
 @param config        Configurations for the `WhiteSdk` object. See [WhiteSdkConfiguration](WhiteSdkConfiguration).
 @param callback      Common event callbacks. See [WhiteCommonCallbackDelegate](WhiteCommonCallbackDelegate).
 @param mixer         Sets RTC audio mixing. See [WhiteAudioMixerBridge](WhiteAudioMixerBridge). When you use the Agora RTC SDK and Interactive Whiteboard SDK at the same time, and the dynamic PPT displayed in the whiteboard contains audio files, you can call the `AudioMixerBridge` interface to play the audio in the dynamic PPT using the Agora RTC SDK interface.
 @return Initialized `WhiteSDK` object.
 */
- (instancetype)initWithWhiteBoardView:(WhiteBoardView *)boardView config:(WhiteSdkConfiguration *)config commonCallbackDelegate:(nullable id<WhiteCommonCallbackDelegate>)callback audioMixerBridgeDelegate:(nullable id<WhiteAudioMixerBridgeDelegate>)mixer;

/**
 Initializes the `WhiteSDK` object.

 **Note:**

 Ensure that you call `WhiteSdk` to initialize a `WhiteSdk` object before calling any other APIs.
 @param boardView     The whiteboard view. See [WhiteBoardView](WhiteBoardView).
 @param config        Configurations for the `WhiteSdk` object. See [WhiteSdkConfiguration](WhiteSdkConfiguration).
 @param callback      Common event callbacks. See [WhiteCommonCallbackDelegate](WhiteCommonCallbackDelegate).
 */
- (instancetype)initWithWhiteBoardView:(WhiteBoardView *)boardView config:(WhiteSdkConfiguration *)config commonCallbackDelegate:(nullable id<WhiteCommonCallbackDelegate>)callback;

/**
 @deprecated This method is deprecated. Use `initWithWhiteBoardView:config:commonCallbackDelegate:` and `initWithWhiteBoardView:config:commonCallbackDelegate:audioMixerBridgeDelegate:` instead.

 Initializes the `WhiteSDK` object.

 @param boardView     The whiteboard view. See [WhiteBoardView](WhiteBoardView).
 @param config        Configurations for the `WhiteSDK` object. See [WhiteSdkConfiguration](WhiteSdkConfiguration).
 */
- (instancetype)initWithWhiteBoardView:(WhiteBoardView *)boardView config:(WhiteSdkConfiguration *)config DEPRECATED_MSG_ATTRIBUTE("initWithWhiteBoardView:config:commonCallbackDelegate");

/**
* Preselects the optimal access domain to improve the connection speed for when the user connects for the first time.
*
* @param appId The unique identifier for a whiteboard project. See [Get security credentials for your whiteboard project](https://docs.agora.io/en/interactive-whiteboard/develop/enable-whiteboard?platform=android#get-security-credentials-for-your-whiteboard-project) for details.
* @param region The data center to select. See [WhiteRegionKey](WhiteRegionKey) for details.
* @param expireSeconds The data cache time (s). Can be nil. The default is 24 hours.
* @param superView The parent view to which the view is attached. Can be nil. The default is `UIApplication.shared.keyWindow`.
*/
+ (void)prepareWhiteConnectionForAppId:(NSString *)appId region:(WhiteRegionKey)region expireSeconds:(NSNumber * _Nullable )expireSeconds attachingSuperView: (UIView * _Nullable)superView;

/**
 Sets audio mixing.
  */
@property (nonatomic, strong, readonly, nullable) WhiteAudioMixerBridge *audioMixer;

#pragma mark

/**
 Declares the fonts that can be used in the local whiteboard.
 @since 2.11.3

 The fonts declared by this method can be used to render the characters in PPT and the characters entered by the text tool.

 Both this method and [loadFontFaces]([WhiteSDK loadFontFaces:completionHandler:]) can declare the fonts to be used in the local whiteboard.
 The difference is that `setupFontFaces` has no callback to report whether the font declaration is successful; loadFontFaces triggers callbacks to report the preload result of each type of font.

 **Note:**

 - This method works only for the local whiteboard and does not affect the font display of the remote whiteboard.
 - Fonts declared by this method will be downloaded only when they are used.
 - Font rendering may vary by device. For example, on some devices, the text will not be rendered until the font has finished loading, while on others, the text will be rendered first using the default font and then refreshed as a whole when the specified font has finished loading.
 - Each time this method is called, it overrides the original font declaration.
 - Do not call this method and the [loadFontFaces]([WhiteSDK loadFontFaces:completionHandler:]) method at the same time; otherwise, unexpected results may occur.

 @param fontFaces The specified fonts. See [WhiteFontFace](WhiteFontFace).
 */
- (void)setupFontFaces:(NSArray <WhiteFontFace *>*)fontFaces;

/**
 Declares the fonts that can be used in the local whiteboard and preloads them.
 @since 2.11.3

 The fonts declared by this method can be used to render the characters in PPT and the characters entered by the text tool.

 Both this method and [setupFontFaces]([WhiteSDK setupFontFaces:]) can declare the fonts to be used in the local whiteboard.
 The difference is that [setupFontFaces]([WhiteSDK setupFontFaces:]) has no callback to report whether the font declaration is successful;
 `loadFontFaces` triggers callbacks to report the preload result of each type of fonts.

 **Note:**

 - This method works only for the local whiteboard and does not affect the font display of the remote whiteboard.
 - Fonts declared by this method will be downloaded only when they are used.
 - Font rendering may vary by device. For example, on some devices, the text will not be rendered until the font has finished loading, while on others, the text will be rendered first using the default font and then refreshed as a whole when the specified font has finished loading.
 - Fonts declared and preloaded by this method cannot be deleted. Each method call adds the new fonts to the already preloaded fonts.
 - Do not call this method and the [setupFontFaces]([WhiteSDK setupFontFaces:]) method at the same time; otherwise, unexpected results may occur.

 @param fontFaces   The specified fonts. See WhiteFontFace.
 @param completionHandler The call result:

 - The `WhiteFontFace` object, if the method call succeeds. See [WhiteFontFace](WhiteFontFace).
 - An error message, if the method call fails.

 Every time a font is loaded, a callback will be triggered to report whether the font has been loaded successfully.
 There will be as many callbacks as there are fonts in the incoming `WhiteFontFace` object.
 */
- (void)loadFontFaces:(NSArray <WhiteFontFace *>*)fontFaces completionHandler:(void (^)(BOOL success, WhiteFontFace *fontFace, NSError * _Nullable error))completionHandler;

/**
 Sets the fonts used by the text tool in the local whiteboard.

 @since 2.11.3

 **Note:**

 - This method only works for the local whiteboard and does not affect the font display of the remote whiteboard.
 - This method cannot set the fonts for rendering the characters in PPT.
 @param fonts Names of the fonts. If the specified font does not exist in the user's system, the text tool cannot use the font. Ensure you call [setupFontFaces]([WhiteSDK setupFontFaces:]) or [loadFontFaces]([WhiteSDK loadFontFaces:completionHandler:]) to preload the specified font into the local whiteboard.
 */
- (void)updateTextFont:(NSArray <NSString *>*)fonts;

#pragma mark - PPT Volume

/**
 Gets the volume of the PPT slide.
 @param completionHandler The result of the method call, including two fields, `volume` and `error`:
                          - A successful call: `volume` ranges from (0,1], indicating the volume of the PPT; `error` returns `nil`.
                          - A failed call: `volume` returns 0; `error` returns the error message.        
*/
- (void)getSlideVolumeWithCompletionHandler:(void(^)(CGFloat volume, NSError *error))completionHandler;

/**
 更新当前 PPT 的音量。
 @param volume 音量值，取值范围为 (0,1]。
 */
- (void)updateSlideVolume:(CGFloat)volume;

#pragma mark - CommonCallback

/**
 Sets common event callbacks.

 The SDK uses the [WhiteCommonCallbackDelegate](WhiteCommonCallbackDelegate) class to report SDK runtime events to the application.

 @param callbackDelegate Common event callbacks. See [WhiteCommonCallbackDelegate](WhiteCommonCallbackDelegate).
 */
- (void)setCommonCallbackDelegate:(nullable id<WhiteCommonCallbackDelegate>)callbackDelegate;

#pragma mark - SlideCallback

/**
 Sets PPT callback events.
 The SDK processes PPT-related callbacks via [WhiteSlideDelegate](WhiteSlideDelegate).
 
 @param slideDelegate PPT callback events，See [WhiteSlideDelegate](WhiteSlideDelegate).
 */
- (void)setSlideDelegate:(nullable id<WhiteSlideDelegate>)slideDelegate;

/**
 Writes the slide log into a specified file.
 
 @param path The path to the specified file. If the file does not exist, it is created. If the file already exists, the slide log is appended to the end of the file.
 @param result The writing result of the log. 
 */
- (void)requestSlideLogToFilePath:(NSString *)path result:(void(^)(BOOL success, NSError *error))result;

@end
NS_ASSUME_NONNULL_END
