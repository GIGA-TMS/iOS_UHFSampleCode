//
//  testViewController.m
//  UHFSample
//
//  Created by Gianni on 2019/11/5.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "testViewController.h"

#import "TwoParameterAPIViewCell.h"
@interface testViewController ()

@end

@implementation testViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    TwoParameterAPIViewCell* ctrler = [[TwoParameterAPIViewCell alloc]init];
    [ctrler.labTitle setText:@"ttt1"];
    [self.stackView addArrangedSubview:ctrler];
//    [self.stackView addSubview:ctrler];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
