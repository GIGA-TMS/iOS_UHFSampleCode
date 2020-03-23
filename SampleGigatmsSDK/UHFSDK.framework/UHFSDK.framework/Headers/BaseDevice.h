//
//  BaseDevice.h
//  GIGATMSSDK
//
//  Created by Gianni on 2019/1/29.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTBaseDevInfo.h"

@class BaseDevice;

@protocol DevConnectionCallback <NSObject>
@optional
- (void)didUpdateConnectionStatus:(BaseDevice*)dev Status:(GTDevConnStatus) connectedState err_code:(int)nErrCode;
@end

@interface BaseDevice : NSObject



@property (nonatomic, strong) id<DevConnectionCallback> connCallback;
/**
 Description

 @return Device Info
 
 */
-(GTBaseDevInfo*)getDevInfo;
-(instancetype)init:(GTBaseDevInfo*) baseDevInfo;
/**
 Description
 https://forums.developer.apple.com/thread/54510
 */
-(void)initBluetooth;
-(void)sendCMD:(NSData*) cmdData;

-(BOOL)changeBLEGATT:(CBUUID*) send Recieve:(CBUUID*) recieve;
-(void)Connect;
-(void)DisConnect;
- (void)baseConnectionStatusChanged:(GTDevConnStatus)devConnStatus err_code:(int)nErrCode UID:(NSString*)strUID;
- (void)didBaseCompleteReadData:(int)read_length data:(NSData*)data;
- (void)didBaseCompleteWriteData:(int)write_length data:(NSData*)data;
- (void)didBaseCompleteReadBLEData:(int)read_length data:(NSData*)data channel:(NSString *)channelID;

@end

