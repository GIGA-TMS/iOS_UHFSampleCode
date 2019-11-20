//
//  UHFScanner.h
//  UHFSDK
//
//  Created by Gianni on 2019/3/19.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "BaseScanner.h"
#import "UHFDevice.h"

NS_ASSUME_NONNULL_BEGIN
@class UHFScanner;

@protocol UHFScannerCallback <NSObject>
@optional
-(void)didScanStop;
-(void)didDiscoverDevice:(BaseDevice*)dev;
-(void)didError:(NSString*)strError;
@end

@protocol UHFScannerDebugCallback <NSObject>
@optional
-(void)didDebugWriteRawData:(NSData *)data channel:(NSString *)channelID;
-(void)didDebugReadRawData:(NSData *)data channel:(NSString *)channelID;
@end
@interface UHFScanner : BaseScanner

@property (nonatomic, assign) id<UHFScannerCallback> mUHFScannerCallback;
@property (nonatomic, assign) id<UHFScannerDebugCallback> mUHFScannerDebugCallback;


- (instancetype)init:(id<UHFScannerCallback>)callback ClassVer:(ClassVer)nClassVer;

/**
 start Scan Device
 */
- (void)changeClassVer:(Byte)classVer;
-(void)startScanDevice;

@end

NS_ASSUME_NONNULL_END
