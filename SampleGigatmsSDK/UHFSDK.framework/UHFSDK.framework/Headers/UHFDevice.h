//
//  UHFDevice.h
//  UHFSDK
//
//  Created by Gianni on 2019/3/20.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "IUHFDeviceListener.h"
#import "BaseDevice.h"
NS_ASSUME_NONNULL_BEGIN

@interface UHFDevice : BaseDevice


/**
 SpecifSpecifies the tag data format received at OnTagPresented Event.
 
 - ET_PC_EPC: The ouput data is PC + EPC fields data.
 - ET_PC_EPC_TID: The ouput data is PC + EPC fields + TID bank data.
 - ET_PC_EPC_Data: The ouput data is PC + EPC fields dataand Memory Bank.
 - ET_PC_EPC_TID_Data: The ouput data is PC + EPC fields + TID bank data and Memory Bank.
 */
typedef NS_ENUM(Byte, TagPresentedType){
    //    ET_PC_EPC             = 0xFF,
    //    ET_PC_EPC_TID         = 0xFE,
    //    ET_PC_EPC_Data        = 0xFD,
    //    ET_PC_EPC_TID_Data    = 0xFC,
    //    EVENT_62              = 0x00,
    //    ET_RF80TagEvent         = 0x80 bit:7 is 1
    ET_PC_EPC             = 0xDF,
    ET_PC_EPC_TID         = 0xDE,
    
};

typedef NS_ENUM(Byte, ScanMode){
    TRIGGER_A_LEVEL_CONTROL     = 0x00,
    ALWAYS_SCAN                 = 0xFF
};


/**
 UHF family list type
 
 - UHF_UR0250: UHF Device 1 - UR0250
 - UHF_TS100: UHF Device 2 - TS100
 - UHF_TS800: UHF Device 3 - TS800
 - UHF_PWD100: UHF Device 4 - PWD100
 */
typedef NS_ENUM(Byte, ClassVer){
    UHF_UR0250              = 0x00,
    UHF_TS100               = 0x01,
    UHF_TS800               = 0x02,
    UHF_PWD100               = 0x03,
};

/**
 Specifies the pattern of sounding buzzer
 
 -  BA_Success: Selects success beep sound
 -  BA_Failure: Selects failure beep sounrd
 -  BA_Disable: Selects to turn off beep sound
 -  BA_Auto: Selects to use default beep sound
 */
typedef NS_ENUM(Byte, BuzzerAction){
    BA_Success = 0x00,// Selects success beep sound
    BA_Failure = 0x01,// Selects failure beep sounrd
    BA_Disable = 0xFE,// 254 Selects to turn off beep sound
    BA_Auto = 0xFF,// 255 Selects to use default beep sound
};


/**
 UHF Device callback
 */
@property (nonatomic, assign, nullable) id<IUHFDeviceListener> uhfListener;
@property (nonatomic, assign) ClassVer classVer;

-(instancetype)initWithInfo:(GTBaseDevInfo*) info;

/**
 Set ts800 reply listener
 
 @param listener see IUHFDeviceListener
 */
-(void)setListener:(id<IUHFDeviceListener>)listener;

/**
 Gets the version of SDK library
 
 @return Version
 */
-(NSString *)getSDKVersion;

/**
 Connect to remote device.
 */
-(void)Connect;

#pragma mark - Special Command List


/// send  Special Multi CMD
/// @param datas  Special CMD format
/// @param apiCode software api code
/// @param cmdCount cmd conunt
-(void)cmdMarkMultiCMD:(NSMutableArray*) datas CMDCode:(Byte)apiCode CMDCount:(int)cmdCount;

/// send  Special CMD
/// @param cmdData Special CMD format
-(void)sendGNetCMD:(NSData*)cmdData;

/**
 Initialize Settings
 Initializes the device settings.
 */
-(void)cmdInitializeSettings:(ClassVer) classVer;


-(void)cmdSpecial:(NSData*)cmdData CMDCode:(int)apiCode CMDCount:(int)cmdCount;
-(void)cmdSetSpecialSetting:(BOOL)isTemp Address:(char)iAddr Value:(NSData*)val CMDCode:(int)apiCode;
-(void)cmdGetSpecialSetting:(BOOL)isTemp Address:(char)iAddr ReadLen:(char)readLen CMDCode:(int)apiCode;
/**
 Only for TS100
 Control reader to make a specified sound beep.
 
 @param buzzerCtrl buzzerMode
 */
-(void)cmdControlBuzzer:(BuzzerAction)buzzerAct;




/**
 SetRepeatTime
 
 @param isTemp  If the value is true, this setting will write into EEPROM.
 @param time Unit: 0.1 seconds
 0: Immediately
 1~253: 0.1~25.3 seconds
 *254: Never repeat
 */
-(void)cmdSetRepeatTime:(BOOL) isTemp Time:(Byte) time;

/**
 cmdGetRepeatTime
 
 @param isTemp  If the value is true, this setting will write into EEPROM.
 */
-(void)cmdGetRepeatTime:(BOOL) isTemp;
/**
 Only for TS800 & UR0250
 Set Scan Mode
 
 @param isTemp  If the value is true, this setting will write into EEPROM.
 @param scanMode Scan Mode
 */
-(void)cmdSetScanMode:(BOOL)isTemp  ScanMode:(ScanMode) scanMode;

/**
 Only for TS800 & UR0250
 Get Trigger Source
 
 @param isTemp  If the value is true, this setting will write into EEPROM.
 */

-(void)cmdGetTriggerType:(BOOL)isTemp;

/**
 Only for TS800 & UR0250
 Set Trigger Sourec
 
 @param isTemp  If the value is true, this setting will write into EEPROM.
 @param triggerType The trigger source of inventory.
 */
-(void)cmdSetTriggerType:(BOOL)isTemp TriggerType:(TriggerType) triggerType;


#pragma mark - Special Command Callback

-(void)didSetSpecialSetting:(short)settingAddr Value:(int)settingValue;
-(void)didSetSpecialSetting:(short)settingAddr Values:(NSData *)settingValues;

-(void)didGetSpecialSetting:(int)settingAddr Value:(int)settingValue;
-(void)didGetSpecialSetting:(int)settingAddr Values:(NSData *)settingValues;

#pragma mark - Setting Command List

/**
 Get Q Value
 Gets the starting Q value for the number of slots in the round.
 @param isTemp  If the value is true, this setting will write into EEPROM.
 */
-(void)cmdGetQValue:(BOOL) isTemp;


/**
 Set Q Value
 Sets the starting Q value for the number of slots in the round.
 @param isTemp  If the value is true, this setting will write into EEPROM.
 @param qvalue The starting Q value for the number of slots in the round. The value ranges from 0 to 15.
 */
-(void)cmdSetQValue:(BOOL) isTemp QValue:(Byte) qvalue;


/**
 Get Session & Target
 Gets the session flag used for inventory round.
 Gets the target for inventory round.
 @param isTemp  If the value is true, this setting will write into EEPROM.
 */
-(void)cmdGetSessionAndTarget:(BOOL) isTemp;


/**
 Set Session & Target
 Sets the target for inventory round.
 Sets the session flag used for inventory round.
 
 @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param target Target indicates whether the Select modifies a Tag’s SL flag or its inventoried flag
 @param session The session flag to be selected for an inventory round
 */
-(void)cmdSetSessionAndTarget:(BOOL) isTemp Target:(Target)target Session:(Session) session;


/**
 Get Rf Power
 Gets the RF Power strength.
 @param isTemp  If the value is true, this setting will write into EEPROM.
 */
-(void)cmdGetRfPower:(BOOL)isTemp;

/**
 Sets the RF Power strength.
 
 @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param rfPower Specifies the RF Power strength. The value is ranging from 1 to 27. The default value is 11. (Range:1~27)
 */
-(void)cmdSetRfPower:(BOOL)isTemp RFPower:(Byte) rfPower;


/**
 * Get the RX RF input sensitivity level.
 */
-(void)cmdGetSensitivity:(BOOL)isTemp;

/**
 * Define the RX RF input sensitivity level.
 * <p>
 * RX Sensitivity setting defines the RX input sensitivity level.
 *
 * @param isTemp   Write the sensitivity value to RAM or not. It the value is true, the sensitivity value will be write.
 * @param sensitivity Specifies the RF input sensitivity level.
 */
-(void)cmdSetSensitivity:(BOOL)isTemp RfSensitivityLevel:(RfSensitivityLevel) sensitivity;



/**
 Get Frequency List
 Gets the channel of hopping frequency in MHz.
 @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 */
-(void)cmdGetFrequencyList:(BOOL) isTemp;


/**
 Set Frequency List
 Sets the channel of hopping frequency in MHz.
 @param isTemp If the value is true, this setting will write into EEPROM.
 @param frequencyList Specifies the channel of hopping frequency for reading tag data.
 */
-(void)cmdSetFrequencyList:(BOOL) isTemp List:(NSArray*) frequencyList;

/**
 Set the threshold to raise a TagPresentedEvent(UHFCallback.didDiscoveredTag).
 
 @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param time The period to raising a TagPresentedEvent. range: 1~255 (Unit: 100ms), 0:Always repeating raising event, 255: Never repeating raising event.
 */
-(void)cmdSetTagPresentRepeatInterval:(BOOL)isTemp Time:(int)time;

/**
 Get the threshold to raise a TagRemovedEvent(UHFCallback.didDiscoveredTag).
 
 @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 */
-(void)cmdGetTagPresentRepeatInterval:(BOOL)isTemp;


/**
 Set the threshold to raise a TagRemovedEvent(UHFCallback.didTagRemoved).
 
 @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 @param round The count of missing discovering tag threshold of inventory rounds.
 */
-(void)cmdSetTagRemoveThreshold:(BOOL)isTemp Round:(int)round;

/**
 Get the threshold to raise a TagRemovedEvent(UHFCallback.didTagRemoved).
 
 @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
 */
-(void)cmdGetTagRemoveThreshold:(BOOL)isTemp;


/// Set the InventoryRoundInterval
/// /// @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
/// @param tenMilliSeconds The period to start an inventory round. Range: 0~254*10s. 255 represent 0;
-(void)cmdSet:(BOOL)isTemp InventoryRoundInterval:(int)tenMilliSeconds;


/// Get the InventoryRoundInterval
/// @param isTemp True value specifies the changes are temporary overwrides for settings. The changes are not saved into the EEPROM and take immediate effect (no rebooting required). False value specifies the changes are permanently overwrides for settings And also saved into the EEPROM. The changes will keep after rebooting the device.
-(void)cmdGetInventoryRoundInterval:(BOOL)isTemp;


#pragma mark - Command List

/**
 Get Device Information
 Gets the firmware program version running on the device.
 */
-(void)cmdGetFirmwareVersion;

/**
 Start Inventory mEPC Tag.
 Starts the process of tag inventory using specified trigger source.
 @see IUHFDeviceListener
 @see  didEventTagPresented:
 @seealso GNPTagInfo
 
 @param tagPresentedType Specify the way of triggering the RF power to read tag data.
 */
-(void)cmdStartInventory:(TagPresentedType) tagPresentedType;

/**
 * Start inventory tags with specific encoded data type.
 
 @param tagDataEncodeType ex:tagDataEncodeType = UDC | EAN_UPC_EAS;
 */
-(void)cmdStartInventoryEx:(TagDataEncodeType) tagDataEncodeType;
/**
 Stop Inventory mEPC Tag.
 Stops the process of tag inventory.
 @see  didGeneralSuccess:
 */
-(void)cmdStopInventory;






/**
 Write EPC
 
 @param hexAccessPassword The password of the tag.
 @param epcData The epc data that is going to write into tag.
 */
-(void)cmdWriteEPC:(NSString*)hexAccessPassword EPCData:(NSData*)epcData;


/**
 Write EPC
 
 @param hexAccessPassword Specifies the password to write data.
 @param memoryBank Specifies which memory bank to write.
 @param startWordAddress Specifies the start word address of memory bank to write data.When write EPC bank, notice that EPC starts from address 02, the first two 2 words are for CRC and PC.
 @param data Specifies the data to write to memory bank. 
 */
-(void)cmdWriteTag:(NSString*)hexAccessPassword MemoryBank:(MemoryBank)memoryBank StartAddr:(int)startWordAddress Data:(NSData*)data;

/**
 Write EPC
 
 @param hexSelectedPcEpc Specifies the tag PC EPC to be selected.
 @param hexAccessPassword Specifies the password to write data.
 @param memoryBank Specifies which memory bank to write.
 @param startWordAddress Specifies the start word address of memory bank to write data.When write EPC bank, notice that EPC starts from address 02, the first two 2 words are for CRC and PC.
 @param data Specifies the data to write to memory bank.
 */
-(void)cmdWriteSelectTag:(NSString*)hexSelectedPcEpc PWD:(NSString*)hexAccessPassword MemoryBank:(MemoryBank)memoryBank StartAddr:(int)startWordAddress Data:(NSData*)data;
/**
 Read EPC
 Reads tag data from given memory bank.
 
 @param password Password of the tag that is going to read. (4 byte/2 Hex String)
 */
-(void)cmdReadEPC:(NSString*)password;


/// Read Tag
/// @param hexSelectedPcEpc Specifies the tag PC EPC to be selected.
/// @param hexAccessPassword Specifies the password to write data.
/// @param memoryBank Specifies which memory bank to write.
/// @param startWordAddress Specifies the start word address of memory bank to read data.When read EPC bank, notice that EPC starts from address 02, the first two 2 words are for CRC and PC.
/// @param readLength Specifies the length to read from memory bank.
-(void)cmdReadTag:(NSString*) hexSelectedPcEpc PWD:(NSString*)hexAccessPassword MemoryBank:(MemoryBank) memoryBank StartAddr:(int)startWordAddress ReadLen:(int)readLength;

/// Read Tag
/// @param hexAccessPassword Specifies the password to write data.
/// @param memoryBank Specifies which memory bank to write.
/// @param startWordAddress Specifies the start word address of memory bank to read data.When read EPC bank, notice that EPC starts from address 02, the first two 2 words are for CRC and PC.
/// @param readLength Specifies the length to read from memory bank.
-(void)cmdReadTagWithPWD:(NSString*)hexAccessPassword MemoryBank:(MemoryBank) memoryBank StartAddr:(int)startWordAddress ReadLen:(int)readLength;

/// Use `accessPassword` to Lock the first tag that is inventoried.
/// @param accessPassword Access Password
/// @param lockInfos The Lock Action to specified memory bank. see GNPLockInfos.h
-(void)cmdLockTag:(NSString*)accessPassword LockInfos:(NSMutableArray*)lockInfos;


/// Lock the first tag that is inventoried.
/// The Access password is decided by the remote connected device.
/// @param lockInfos The Lock Action to specified memory bank. see GNPLockInfos.h
-(void)cmdLockTag:(NSMutableArray*)lockInfos;


/// Kill Tag
/// @param hexAccessPassword Access Password
/// @param hexKillPassword Kill Password
-(void)cmdKillTag:(NSString*)hexAccessPassword KillPWD:(NSString*)hexKillPassword;


/// Kill Tag
/// @param hexKillPassword Kill Password
-(void)cmdKillTag:(NSString*)hexKillPassword;

@end

NS_ASSUME_NONNULL_END
