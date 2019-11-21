//
//  BaseScanner.h
//  GIGATMSSDK
//
//  Created by Gianni on 2019/1/28.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTCommonHeader.h"
#import "GTBLEDevInfo.h"
#import "GTBLEScanInfo.h"
#import "GTBaseDevInfo.h"

@class BaseScanner;

@interface BaseScanner : NSObject
{
}

@property (nonatomic, assign) GTConnectType mConnectType;

-(instancetype)init:(GTBaseDevInfo*) baseDevInfo;
-(instancetype)initByUDP:(int) port;
-(instancetype)initByBLE:(GTBLEScanInfo*)bleInfo;
-(void)changeConnectType:(GTConnectType)connType;
-(void)sendCMD:(NSData*) cmdData;
-(void)didCompleteUDPReadData:(int)read_length data:(NSData*)data channel:(NSString*)channelID;
-(void)didCompleteUDPWriteData:(int)write_length data:(NSData*)data;
-(void)startScanDevice;
-(void)setScanTime:(double)time;
-(void)stopScan;
-(void)didBaseDiscoverBLEDevice:(GTBLEDevInfo *)dev data:(NSData* )data;
-(void)didBaseScanStop;

@end

