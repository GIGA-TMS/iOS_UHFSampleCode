//
//  UR0250.h
//  UHFSDK
//
//  Created by Gianni on 2019/4/29.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import <UHFSDK/UHFSDK.h>
#import "UHFDevice.h"
#import "IUR0250Listener.h"
NS_ASSUME_NONNULL_BEGIN

@interface UR0250 : UHFDevice



@property (nonatomic, assign) id<IUR0250Listener> ur0250Listener;

/**
 Initialize setting of UR0250, please call it after connected with remote UR0250.
 */
-(void)cmdInitializeSettings;
@end

NS_ASSUME_NONNULL_END
