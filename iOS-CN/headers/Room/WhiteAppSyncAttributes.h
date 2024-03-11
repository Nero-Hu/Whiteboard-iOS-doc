//
//  WhiteAppSyncAttributes.h
//  Whiteboard
//
//  Created by xuyunshi on 2023/8/23.
//

#import "WhiteObject.h"

NS_ASSUME_NONNULL_BEGIN

/** 多窗口模式下，小窗应用的相关信息。*/
@interface WhiteAppSyncAttributes : WhiteObject

/** 小窗应用类型。 */
@property (nonatomic, copy, readonly) NSString *kind;
/** 小窗应用标题。 */
@property (nonatomic, copy, readonly) NSString *title;
/** 小窗应用参数。 */
@property (nonatomic, copy, readonly) NSDictionary *options;
/** 小窗应用可选数据源。 */
@property (nonatomic, copy, readonly, nullable) NSString *src;
/** 小窗应用可选状态。 */
@property (nonatomic, copy, readonly) NSDictionary *state;


@end

NS_ASSUME_NONNULL_END
