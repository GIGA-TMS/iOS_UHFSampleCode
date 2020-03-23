//
//  TS100.h
//  UHFSDK
//
//  Created by Gianni on 2019/4/29.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import <UHFSDK/UHFSDK.h>
#import "UHFDevice.h"
NS_ASSUME_NONNULL_BEGIN


typedef NS_ENUM(Byte, TS100SpecialCode){
    SW_EE_TS100_getBleDeviceName      = 0x00,
};



@protocol ITS100SpecialListener <NSObject>
@optional

@end



@interface TS100 : UHFDevice

/**
 Initialize setting of TS100, please call it after connected with remote TS100.
 */
-(void)cmdInitializeSettings;


/**
 Get Filter
 
 @param isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 
 */
-(void)cmdGetFilter:(BOOL) isTemp;


/**
 Set Filters
 
 @param isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param filterTypes Specifies the decoded type for reading tag data.
 */
-(void)cmdSetFilter:(BOOL) isTemp TagDataEncodeType:(TagDataEncodeType) filterTypes;



/**
 Get Post Data Delimiter & Memory Bank Selection setting.
 
 @param isTemp isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 */
-(void)cmdGetPostDataDelimiterAndMemoryBankSelection:(BOOL) isTemp;
/**
 Set Post Data Delimiter
 
 @param isTemp isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param postDataDelimiter Specifies the delimiter append to the end of output data.
 @param memoryBankSelections Memory Bank Selections setting.
 */
-(void)cmdSet:(BOOL) isTemp PostDataDelimiter:(PostDataDelimiter) postDataDelimiter MemoryBankSelection:(MemoryBankSelection) memoryBankSelections;


/**
 Start inventory tags with specific encoded data type.
 */
-(void)cmdStartInventoryEx;


/**
 Gets the event command type.
 
 @param isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 
 */
-(void)cmdGetEventType:(BOOL) isTemp;

/**
 Sets the event command type.
 
 @param isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 
 @param eventType The type for the event command.
 */
-(void)cmdSet:(BOOL) isTemp EventType:(EventType) eventType;


/**
 Gets the data output interface.
 
 @param isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 
 */
-(void)cmdGetOutputInterface:(BOOL) isTemp;


//"(boolean temporary, 單選KeyboardSimulation,多選OutputInterface)

/**
 Set the data output interface.
 
 @param isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 
 @param keyboardSimulation Keyboard Simulation
 @param outputInterface  The set of data output interface. also can 'outputInterface = OI_HID_N_VCOM | OI_BLE;'
 */
-(void)cmdSet:(BOOL) isTemp KeyboardSimulation:(KeyboardSimulation) keyboardSimulation OutputInterface:(OutputInterface) outputInterface;



/**
 Get Device BLE module
 Gets the firmware program version running on the device BLE module.
 */
-(void)cmdGetBleRomVersion;


/// Get Device BLE Neme
-(void)cmdGetBleDeviceName;

/// Set Device BLE Neme
/// @param devName Device BLE Neme
-(void)cmdSetBleDeviceName:(NSString*)devName;


/**
 Only for TS100
 Gets the repeats mode of sounding the beep with the same pattern.
 
 @param isTemp  If the value is true, this setting will write into EEPROM.
 */
-(void)cmdGetBuzzerOperationMode:(BOOL) isTemp;

/**
 Only for TS100
 SetBuzzerOperationMode
 Sets the repeats mode of sounding the beep with the same pattern.
 @param isTemp  If the value is true, this setting will write into EEPROM.
 @param bom Buzzer Operation Mode:Specifies the repeats mode of sounding the beep with the same pattern.
 */
-(void)cmdSet:(BOOL) isTemp BuzzerOperationMode:(BuzzerOperationMode) bom;

-(void)cmdSetWifiSettings:(NSString*)strSSID PWD:(NSString*)strPwd;
-(void)cmdSetWifiSettings:(NSString*)strSSID PWD:(NSString*)strPwd IP:(NSString*)strIP Gateway:(NSString*)strGateway  SubNetMask:(NSString*)strSubNetMask;
@end

NS_ASSUME_NONNULL_END
