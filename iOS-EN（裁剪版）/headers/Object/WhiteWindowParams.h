//
//  WhiteWindowParams.h
//  Whiteboard
//
//  Created by yleaf on 2022/2/9.
//

#import "WhiteObject.h"

NS_ASSUME_NONNULL_BEGIN


typedef NSString * WhitePrefersColorScheme NS_STRING_ENUM;
/** `WhitePrefersColorSchemeAuto` applies only to iOS 13 and above.*/
FOUNDATION_EXPORT WhitePrefersColorScheme const WhitePrefersColorSchemeAuto;
FOUNDATION_EXPORT WhitePrefersColorScheme const WhitePrefersColorSchemeLight;
FOUNDATION_EXPORT WhitePrefersColorScheme const WhitePrefersColorSchemeDark;

/** Whiteboard window parameters.*/
@interface WhiteWindowParams : WhiteObject

/** Whether the window is displayed in fullscreen mode. The default value is `NO`. */
@property (nonatomic, assign) BOOL fullscreen;
/** Use CSS to override the style of whiteboard windows. */
@property (nonatomic, copy) NSString *overwriteStyles;

@end

NS_ASSUME_NONNULL_END
