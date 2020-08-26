function CodeDefine() { 
this.def = new Array();
this.def["Phi_PID_D"] = {file: "UniControlSystem_c.html",line:19,type:"var"};
this.def["Phi_PID_I"] = {file: "UniControlSystem_c.html",line:22,type:"var"};
this.def["Phi_PID_P"] = {file: "UniControlSystem_c.html",line:25,type:"var"};
this.def["Position"] = {file: "UniControlSystem_c.html",line:28,type:"var"};
this.def["Strom"] = {file: "UniControlSystem_c.html",line:31,type:"var"};
this.def["x_PID_D"] = {file: "UniControlSystem_c.html",line:34,type:"var"};
this.def["x_PID_HLIM"] = {file: "UniControlSystem_c.html",line:37,type:"var"};
this.def["x_PID_I"] = {file: "UniControlSystem_c.html",line:42,type:"var"};
this.def["x_PID_LLIM"] = {file: "UniControlSystem_c.html",line:45,type:"var"};
this.def["x_PID_P"] = {file: "UniControlSystem_c.html",line:50,type:"var"};
this.def["rtP"] = {file: "UniControlSystem_c.html",line:55,type:"var"};
this.def["rtDW"] = {file: "UniControlSystem_c.html",line:120,type:"var"};
this.def["rtM_"] = {file: "UniControlSystem_c.html",line:123,type:"var"};
this.def["rtM"] = {file: "UniControlSystem_c.html",line:124,type:"var"};
this.def["UniControlSystem_Step"] = {file: "UniControlSystem_c.html",line:157,type:"fcn"};
this.def["UniControlSystem_Init"] = {file: "UniControlSystem_c.html",line:465,type:"fcn"};
this.def["RT_MODEL"] = {file: "UniControlSystem_h.html",line:38,type:"type"};
this.def["DW"] = {file: "UniControlSystem_h.html",line:46,type:"type"};
this.def["P"] = {file: "UniControlSystem_h.html",line:114,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:47,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:48,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:50,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:86,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["UniControlSystem_c.html"] = "../UniControlSystem.c";
	this.html2Root["UniControlSystem_c.html"] = "UniControlSystem_c.html";
	this.html2SrcPath["UniControlSystem_h.html"] = "../UniControlSystem.h";
	this.html2Root["UniControlSystem_h.html"] = "UniControlSystem_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"UniControlSystem_c.html","UniControlSystem_h.html","rtwtypes_h.html","rtmodel_h.html"];
