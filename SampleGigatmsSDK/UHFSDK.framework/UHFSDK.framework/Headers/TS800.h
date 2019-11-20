//
//  TS800.h
//  UHFSDK
//
//  Created by Gianni on 2019/4/29.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "UHFDevice.h"

NS_ASSUME_NONNULL_BEGIN

@interface TS800 : UHFDevice
/**
 Initialize setting of TS800, please call it after connected with remote TS800.
 */
-(void)cmdInitializeSettings;
@end

NS_ASSUME_NONNULL_END
