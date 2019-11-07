//
//  ScanBaseDevTableViewController.m
//  UHFSample
//
//  Created by Gianni on 2019/4/2.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "ScanBaseDevTableViewController.h"
#import "BaseDevItemTableViewCell.h"
#import <UHFSDK/UHFScanner.h>
#import <UHFSDK/UHFDevice.h>
#import <UHFSDK/GTDeviceManager.h>
#import "DevDetailTabBarViewController.h"

//extern NSMutableArray* g_BaseDevs;

@interface ScanBaseDevTableViewController () <UHFScannerCallback,DevConnectionCallback>

@end

@implementation ScanBaseDevTableViewController
{
    NSMutableDictionary* allBaseDevList;
    UHFScanner* uhfScanner;
    NSMutableArray* g_BaseDevs;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    allBaseDevList = [[NSMutableDictionary alloc]init];
    
    if (g_BaseDevs == nil) {
        g_BaseDevs = [[NSMutableArray alloc] init];
    }
    uhfScanner = [[UHFScanner alloc]init:self ClassVer:UHF_TS100];
    [self refresh];

    
   
}

-(void)refresh{
    [self.tableView reloadData];
    self.tableView.contentInset = UIEdgeInsetsMake(0, -10, 0, 10);
}
- (IBAction)actScanDev:(id)sender {
    [g_BaseDevs removeAllObjects];
    [[GTDeviceManager sharedDeviceManager]removeAllDevice];
    if ([sender isOn]) {
        [uhfScanner startScanDevice];
    }else {
        [uhfScanner stopScan];
    }
}
- (IBAction)actUseWiFi:(id)sender {
    [g_BaseDevs removeAllObjects];
    [[GTDeviceManager sharedDeviceManager]removeAllDevice];
    [self refresh];
    if ([sender isOn]) {
        [uhfScanner changeConnectType:Type_WiFi_UDP];
    }else {
        [uhfScanner changeConnectType:Type_BLE];
    }
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return g_BaseDevs.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    BaseDevItemTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"BaseDevScanCell" forIndexPath:indexPath];
    if (!g_BaseDevs) {
        return cell;
    }
    BaseDevice* temp = [g_BaseDevs objectAtIndex:indexPath.row];
    
    if (temp) {
        cell.labDevName.text = temp.getDevInfo.devName;
        cell.labDevInfo.text = temp.getDevInfo.devUidInfo;
        cell.labConnStauts.text = temp.getDevInfo.strConnStauts;
        [cell.btnConnect setTag:indexPath.row];
        switch (temp.getDevInfo.currentConnStatus) {
            case DevDisconnected:
            {
                cell.btnConnect.titleLabel.text = @"Connect";
            }
                break;
            case DevConnected:
            {
                cell.btnConnect.titleLabel.text = @"Disconnect";
            }
                break;
            default:
                break;
        }
        [cell.btnConnect addTarget:self
                            action:@selector(actConnect:) forControlEvents:UIControlEventTouchDown];
        
        [cell.btnCtrl setTag:indexPath.row];
        [cell.btnCtrl addTarget:self
                         action:@selector(actCtrl:) forControlEvents:UIControlEventTouchDown];
        
    }
    return cell;
}

-(void)actCtrl:(id)sender{
    BaseDevice* temp = [g_BaseDevs objectAtIndex:[sender tag]];
    if (temp) {
        UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        DevDetailTabBarViewController* ctrler =[storyboard instantiateViewControllerWithIdentifier:@"DevDetailCtrl"];
        [ctrler setPassDev:((UHFDevice*)temp)];
        ctrler.title = temp.getDevInfo.devName;
        [self.navigationController pushViewController:ctrler animated:YES];
    }
    
    
}
-(void)actConnect:(id)sender{
    BaseDevice* temp = [g_BaseDevs objectAtIndex:[sender tag]];
    if (temp) {
        switch (temp.getDevInfo.currentConnStatus) {
            case DevDisconnected:
            {
                [temp Connect];
            }
                break;
            case DevConnected:
            {
                [temp DisConnect];
            }
                break;
            default:
                 [temp DisConnect];
                break;
        }
        
        
        [self refresh];
    }
}

-(void)didScanStop{
    [_swScanDev setOn:false];
}
-(void)didDiscoverDevice:(BaseDevice*)dev{
    NSLog(@"UI didDiscoverDevice dev = %@",dev.debugDescription);
    GTBaseDevInfo* devInfo = dev.getDevInfo;
    BaseDevice* addDev = [[GTDeviceManager sharedDeviceManager]addDevice:devInfo];
    if(addDev) {
        [addDev setConnCallback:self];
        if(g_BaseDevs) {
            [g_BaseDevs addObject:addDev];
        }
        
    }
    [self refresh];
}
-(void)didError:(NSString*)strError{
    
}

- (void)didUpdateConnectionStatus:(BaseDevice*)dev Status:(GTDevConnStatus) connectedState err_code:(int)nErrCode{
    [self refresh];
}



@end
