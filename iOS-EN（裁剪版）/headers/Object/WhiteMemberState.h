//
//  MemberState.h
//  WhiteSDK
//
//  Created by leavesster on 2018/8/14.
//

#import "WhiteObject.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - ApplianceName
/**
 Whiteboard tools.
 */
typedef NSString * WhiteApplianceNameKey NS_STRING_ENUM;

/** Clicker, which can be used for clicking and selectin content on the HTML5 file.*/
extern WhiteApplianceNameKey const ApplianceClicker;

/** Pencil. */
extern WhiteApplianceNameKey const AppliancePencil;
/** Selector. */
extern WhiteApplianceNameKey const ApplianceSelector;
/** Text input box. */
extern WhiteApplianceNameKey const ApplianceText;
/** Ellipse. */
extern WhiteApplianceNameKey const ApplianceEllipse;
/** Rectangle. */
extern WhiteApplianceNameKey const ApplianceRectangle;
/** Eraser. */
extern WhiteApplianceNameKey const ApplianceEraser;
/**
 * A pencil eraser used to erase any part of the pencil strokes.
 * This tool only applies for NewPencil. You need to set disableNewPencil to false before using the pencil eraser. 
 */
extern WhiteApplianceNameKey const AppliancePencilEraser;
/** Straight line. */
extern WhiteApplianceNameKey const ApplianceStraight;
/** Arrow. */
extern WhiteApplianceNameKey const ApplianceArrow;
/** Hand. */
extern WhiteApplianceNameKey const ApplianceHand;
/** Laser pointer. */
extern WhiteApplianceNameKey const ApplianceLaserPointer;
/** Shape tool. You need to set the `ShapeType` property. The default value is `ApplianceShapeTypeTriangle`.
 @since 2.12.24 */
extern WhiteApplianceNameKey const ApplianceShape;

#pragma mark - ShapeKey

/** TShape types. */
typedef NSString * WhiteApplianceShapeTypeKey NS_STRING_ENUM;
/** Triangle.
 @since 2.12.24  */
extern WhiteApplianceShapeTypeKey const ApplianceShapeTypeTriangle;
/** Rhombus.
 @since 2.12.24  */
extern WhiteApplianceShapeTypeKey const ApplianceShapeTypeRhombus;
/** Pentagram.
 @since 2.12.24  */
extern WhiteApplianceShapeTypeKey const ApplianceShapeTypePentagram;
/** Speech bubble.
 @since 2.12.24  */
extern WhiteApplianceShapeTypeKey const ApplianceShapeTypeSpeechBalloon;

#pragma mark - ReadonlyMemberState

/** Settings of the whiteboard tool in use.(Readonly) */
@interface WhiteReadonlyMemberState : WhiteObject

/** The name of the whiteboard tool currently in use. */
@property (nonatomic, copy, readonly) WhiteApplianceNameKey currentApplianceName;
/** The stroke color in RGB format, for example, `0, 0, 255` (blue). */
@property (nonatomic, copy, readonly) NSArray<NSNumber *> *strokeColor;
/** The stroke width. */
@property (nonatomic, strong, readonly) NSNumber *strokeWidth;
/** The font size of the text.  */
@property (nonatomic, strong, readonly) NSNumber *textSize;
/** Text color in RGB format, for example, (0, 0, 255) represents blue. */
@property (nonatomic, copy, readwrite, nullable) NSArray<NSNumber *> *textColor;
/** Size of the eraser for local erasing. The value range is [1,3], where a larger value represents a larger size. */
@property (nonatomic, strong, readwrite, nullable) NSNumber *pencilEraserSize;

/** The opacity of the stroke.
 * @since 2.16.112
 * The value range is [0.0, 1.0], where 0 represents completely transparent and 1 represents completely opaque.
 * Only effective when `WhiteSdkConfiguration.enableAppliancePlugin` is enabled.
 */
@property (nonatomic, strong, readonly, nullable) NSNumber *strokeOpacity;
/** The fill color.
 * @since 2.16.112
 * Only effective when `WhiteSdkConfiguration.enableAppliancePlugin` is enabled.
 */
@property (nonatomic, copy, readonly, nullable) NSArray<NSNumber *> *fillColor;
/** The opacity of the fill.
 * @since 2.16.112
 * The value range is [0.0, 1.0], where 0 represents completely transparent and 1 represents completely opaque.
 * Only effective when `WhiteSdkConfiguration.enableAppliancePlugin` is enabled.
*/
@property (nonatomic, strong, readonly, nullable) NSNumber *fillOpacity;

@end

/** Settings of the whiteboard tool in use. */
@interface WhiteMemberState : WhiteReadonlyMemberState
/** The name of the whiteboard tool currently in use. */
@property (nonatomic, copy, readwrite) WhiteApplianceNameKey currentApplianceName;
/** The stroke color in RGB format, for example, `0, 0, 255` (blue). */
@property (nonatomic, copy, readwrite) NSArray<NSNumber *> *strokeColor;
/** The stroke width. */
@property (nonatomic, strong, readwrite) NSNumber *strokeWidth;
/** The font size of the text. */
@property (nonatomic, strong, readwrite) NSNumber *textSize;
/** Text color in RGB format, for example, (0, 0, 255) represents blue. */
@property (nonatomic, copy, readwrite, nullable) NSArray<NSNumber *> *textColor;
/** Size of the eraser for local erasing. The value range is [1,3], where a larger value represents a larger size. */
@property (nonatomic, strong, readwrite, nullable) NSNumber *pencilEraserSize;
/**
 Whether to allow directly selecting and editing whiteboard text:
 
 - `YES`: Allow directly selecting and editing whiteboard text.
 - `NO`: (Default) Do not allow directly selecting and editing whiteboard text.
 */
@property (nonatomic, assign, readwrite, nullable) NSNumber *textCanSelectText;
/**
 Whether to support drawing dotted lines:
 You need to set `disableNewPencil` to `false` before joining the channel.

 - `YES`: Support drawing dotted lines.
 - `NO`: (Default) Do not support drawing dotted lines.
 */
@property (nonatomic, assign, readwrite, nullable) NSNumber *dottedLine;
@end
