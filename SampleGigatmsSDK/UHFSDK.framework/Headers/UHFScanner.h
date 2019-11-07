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
@interface UHFScanner : BaseScanner

@property (nonatomic, assign) id<UHFScannerCallback> mUHFScannerCallback;


- (instancetype)init:(id<UHFScannerCallback>)callback ClassVer:(ClassVer)nClassVer;

/**
 start Scan Device
 */
- (void)changeClassVer:(Byte)classVer;
-(void)startScanDevice;

@end

NS_ASSUME_NONNULL_END
