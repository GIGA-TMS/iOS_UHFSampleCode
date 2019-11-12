//
//  InventoryViewController.m
//  UHFSample
//
//  Created by Gianni on 2019/4/12.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "InventoryViewController.h"
#import "TagItemTableViewCell.h"
#import <UHFSDK/GNPTagInfo.h>
#import "DevDetailTabBarViewController.h"
#import "DevConnStatusViewController.h"
#import "MBProgressHUD.h"

@interface InventoryViewController () <UITableViewDelegate, UITableViewDataSource, IUHFDeviceListener>

@end

@implementation InventoryViewController
{
    NSMutableArray* allTagItems;
    UHFDevice* passDev;
    DevConnStatusViewController* childViewController;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    if (passDev) {
        [passDev setListener:self];
        
        
        
    }
    allTagItems = [[NSMutableArray alloc]init];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [passDev setListener:self];
}


-(void)viewDidDisappear:(BOOL)animated {
//    [passDev setListener:nil];
}
- (IBAction)actInitalizeSettings:(id)sender {
    [passDev cmdInitializeSettings:passDev.classVer];
}
- (IBAction)actGetBLEVer:(id)sender {
    [passDev cmdGetBLEFirmwareVersion];
}

- (IBAction)actInventoryEx:(id)sender {
    [passDev cmdStartInventoryEx:TDE_RAW_DATA];}

- (IBAction)actInventory:(id)sender {
    [passDev cmdStartInventory:ET_PC_EPC];
}
- (IBAction)actStopInventory:(id)sender {
    [passDev cmdStopInventory];
}
- (IBAction)actClearList:(id)sender {
    [allTagItems removeAllObjects];
    [self.tableView reloadData];
}

#pragma mark Tableview Delegate Method


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return allTagItems.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    TagItemTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"TagItemCell" forIndexPath:indexPath];
    
    
    GNPTagInfo* tagItem = [allTagItems objectAtIndex:indexPath.row];
    
    
    NSString* strNo;
    NSString* strEPC;
    NSString* strCount;
    
    
    strNo = [NSString stringWithFormat:@"%ld",(long)indexPath.row];
    strEPC = [NSString stringWithFormat:@"%@",tagItem.EPCHexString];
    strCount = [NSString stringWithFormat:@"%d",tagItem.Count];
    
    cell.labNo.text = strNo;
    cell.labEPC.text = strEPC;
    cell.labCount.text = strCount;
    
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
}



-(void)delayAction {
    NSLog(@"InventoryViewController delayAction cmdGetFirmwareVersion");
    
      [passDev cmdGetFirmwareVersion];
}


-(void)didGeneralSuccess:(NSString*)strCMDName{
    NSLog(@"InventoryViewController didGeneralSuccess strCMDName = %@",strCMDName);
    
    [self showToast:strCMDName message:@"Success"];
    if ([strCMDName isEqualToString:@"InitializeDevice"]) {
        [self performSelector:@selector(delayAction) withObject:nil afterDelay:0.3];
    }
}
-(void)didGeneralERROR:(NSString*)strCMDName ErrMessage:(NSString*)strErrorMessage{
    
//    [self showToast:strCMDName message:@"ERROR"];
    NSLog(@"InventoryViewController didGeneralERROR");
}
- (void)didGetBLEFirmwareVersion:(NSString *)fwVer {
     NSLog(@"didGetBLEFirmwareVersion = %@",fwVer);
    [passDev getDevInfo]._bleDevInfo.devROMVersion = fwVer;
    if (childViewController) {
           [childViewController updateBLEFirmwareVersion:fwVer];
       }
}
- (void)didGetFirmwareVersion:(NSString *)fwVer {
     NSLog(@"didGetFirmwareVersion = %@",fwVer);
    [passDev getDevInfo].devROMVersion = fwVer;
    if (childViewController) {
        [childViewController reloadData];
    }
    
    [passDev cmdGetBLEFirmwareVersion];
}


-(void)didGetRfPower:(int)rfPower{
    
}
-(void)didGetSensitivity:(RfSensitivityLevel)rfSensitivity{
    
}
-(void)didGetTriggerType:(TriggerType)triggerType{
    
}

- (void)didDiscoverTagInfoEx:(GNPDecodedTagData *)decodedTagData {
    NSLog(@"didDiscoverTagInfoEx");
    GNPTagInfo* taginfo = [[GNPTagInfo alloc]init];
    taginfo.EPCHexString = [decodedTagData getTIDHexString];
    if ([allTagItems count] == 0) {
        [allTagItems addObject:taginfo];
    }else {
        int countList = 0;
        for (int i = 0; i < [allTagItems count]; i++) {
            
            GNPTagInfo* temp = [allTagItems objectAtIndex:i];
            if ([temp.EPCHexString isEqualToString:taginfo.EPCHexString]) {
                [temp updateCount:temp.Count+1];
                [allTagItems replaceObjectAtIndex:i withObject:temp];
            }else {
                countList++;
            }
        }
        if (countList == [allTagItems count]) {
            [allTagItems addObject:taginfo];
        }
    }
    [self.tableView reloadData];
}

-(void)didEventTagPresented:(GNPTagInfo*)taginfo{
    if ([allTagItems count] == 0) {
        [allTagItems addObject:taginfo];
    }else {
        int countList = 0;
        for (int i = 0; i < [allTagItems count]; i++) {
            
            GNPTagInfo* temp = [allTagItems objectAtIndex:i];
            if ([temp.EPCHexString isEqualToString:taginfo.EPCHexString]) {
                [temp updateCount:temp.Count+1];
                [allTagItems replaceObjectAtIndex:i withObject:temp];
            }else {
               countList++;
            }
        }
        if (countList == [allTagItems count]) {
            [allTagItems addObject:taginfo];
        }
    }
    [self.tableView reloadData];
}
-(void)didEventTagRemoved:(GNPTagInfo*)taginfo{
    
}

- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    NSString * segueName = segue.identifier;
    if ([segueName isEqualToString: @"DevConnStatusView"]) {
        
        DevDetailTabBarViewController* ctrler = (DevDetailTabBarViewController*)self.tabBarController;
        passDev = [ctrler getUHFDevice];
        
        
        
        childViewController = (DevConnStatusViewController *) [segue destinationViewController];
        [childViewController setUHFDevice:passDev];
    }
}



-(void)showToast:(NSString*)title message:(NSString*)message {
    
    
    
    NSMutableString* allMesg = [NSMutableString stringWithString:title];
    [allMesg appendString:@" "];
    [allMesg appendString:message];
    
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.label.text = allMesg;
    hud.removeFromSuperViewOnHide = YES;
    [hud hideAnimated:YES afterDelay:1];
}


@end
