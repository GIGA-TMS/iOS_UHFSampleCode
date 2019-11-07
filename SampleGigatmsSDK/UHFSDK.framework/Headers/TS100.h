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
 Get Post Data Delimiter
 
 @param isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 
 */
-(void)cmdGetPostDataDelimiter:(BOOL) isTemp;


/**
 Set Post Data Delimiter
 
 @param isTemp isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param postDataDelimiter Specifies the delimiter append to the end of output data.
 */
-(void)cmdSetPostDataDelimiter:(BOOL) isTemp PostDataDelimiter:(PostDataDelimiter) postDataDelimiter;



/**
 Get Memory Bank Selection setting.
 
 @param isTemp isTemp isTemp True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrites for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 */
-(void)cmdGetMemoryBankSelection:(BOOL) isTemp;

/**
 Set Memory Bank Selections setting.
 When the filter is disable (`disableFilter`).This setting decides the output memory bank data.
 The data will get from `UHFCallback.didDiscoverTagInfoEx` and KeyboardSimulation.
 
 @param isTemp           True value specifies the changes are temporary overwrites for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param memoryBankSelections Memory Bank Selections setting.
 
 */
-(void)cmdSetMemoryBankSelection:(BOOL) isTemp MemoryBankSelection:(MemoryBankSelection) memoryBankSelections;


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
-(void)cmdSetEventType:(BOOL) isTemp EventType:(EventType) eventType;


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
-(void)cmdSetOutputInterface:(BOOL) isTemp KeyboardSimulation:(KeyboardSimulation) keyboardSimulation OutputInterface:(OutputInterface) outputInterface;


@end

NS_ASSUME_NONNULL_END
