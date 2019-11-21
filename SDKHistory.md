SDK History
===========

2.0.0.21 (2019/11/21)
---------------------

### Update

- change new "Update EEPROM to Register" function
- fixed multiple ACK function

2.0.0.16 (2019/11/20)
---------------------

### Update

- add UHFScannerDebugCallback
- fixed Update EEPROM to Register function

2.0.0.15 (2019/11/20)
---------------------

### Update

- fixed lock timeout

2.0.0.14 (2019/11/15)
---------------------

### Update

- change Lock function

2.0.0.13 (2019/11/14)
---------------------

### Update

- fixed FIFO bug
	

2.0.0.12 (2019/11/12)
---------------------

### Update

-	add readSetting FIFO

```
-(void)cmdSet:(BOOL)isTemp InventoryRoundInterval:(int)tenMilliSeconds;
-(void)cmdGetInventoryRoundInterval:(BOOL)isTemp;
```


2.0.0.11 (2019/11/01)
---------------------

### Update

-	InventoryEx command format

2.0.0.10 (2019/10/29)
---------------------

### Update

-	APIs parameter description
-	Callback implementation
