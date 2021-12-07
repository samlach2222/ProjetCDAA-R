function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();
	
	if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/CDAA-R.exe", "@StartMenuDir@/CDAA-R.lnk", "workingDirectory=@TargetDir@",  "description=Démarre CDAA-R");
		component.addOperation("CreateShortcut", "@TargetDir@/CDAA-R.exe", "@DesktopDir@/CDAA-R.lnk", "workingDirectory=@TargetDir@", "description=Démarre CDAA-R");
    }
}
