function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/In1 */
	this.urlHashMap["UniControlSystem:1"] = "UniControlSystem.c:141";
	/* <Root>/Constant */
	this.urlHashMap["UniControlSystem:81"] = "UniControlSystem.c:66,206,211,216,221,226,231,236,241,246,251,256,261,266,271,276&UniControlSystem.h:70";
	/* <Root>/Constant1 */
	this.urlHashMap["UniControlSystem:110"] = "UniControlSystem.c:39,140&UniControlSystem.h:116";
	/* <Root>/Sub1
 */
	this.urlHashMap["UniControlSystem:113"] = "UniControlSystem.c:139";
	/* <Root>/Out1 */
	this.urlHashMap["UniControlSystem:9"] = "UniControlSystem.c:162,165,168";
	/* <Root>/Out2 */
	this.urlHashMap["UniControlSystem:10"] = "UniControlSystem.c:205";
	/* <Root>/Out3 */
	this.urlHashMap["UniControlSystem:11"] = "UniControlSystem.c:210";
	/* <Root>/Out4 */
	this.urlHashMap["UniControlSystem:12"] = "UniControlSystem.c:215";
	/* <Root>/Out5 */
	this.urlHashMap["UniControlSystem:13"] = "UniControlSystem.c:220";
	/* <Root>/Out6 */
	this.urlHashMap["UniControlSystem:14"] = "UniControlSystem.c:225";
	/* <Root>/Out7 */
	this.urlHashMap["UniControlSystem:15"] = "UniControlSystem.c:230";
	/* <Root>/Out8 */
	this.urlHashMap["UniControlSystem:16"] = "UniControlSystem.c:235";
	/* <Root>/Out9 */
	this.urlHashMap["UniControlSystem:66"] = "UniControlSystem.c:240";
	/* <Root>/Out10 */
	this.urlHashMap["UniControlSystem:67"] = "UniControlSystem.c:245";
	/* <Root>/Out11 */
	this.urlHashMap["UniControlSystem:68"] = "UniControlSystem.c:250";
	/* <Root>/Out12 */
	this.urlHashMap["UniControlSystem:69"] = "UniControlSystem.c:255";
	/* <Root>/Out13 */
	this.urlHashMap["UniControlSystem:70"] = "UniControlSystem.c:260";
	/* <Root>/Out14 */
	this.urlHashMap["UniControlSystem:71"] = "UniControlSystem.c:265";
	/* <Root>/Out15 */
	this.urlHashMap["UniControlSystem:72"] = "UniControlSystem.c:270";
	/* <Root>/Out16 */
	this.urlHashMap["UniControlSystem:73"] = "UniControlSystem.c:275";
	/* <S1>/Constant */
	this.urlHashMap["UniControlSystem:114:1688"] = "UniControlSystem.c:63,299&UniControlSystem.h:67";
	/* <S1>/Derivative Gain */
	this.urlHashMap["UniControlSystem:114:1668"] = "UniControlSystem.c:20,147&UniControlSystem.h:97";
	/* <S1>/Filter */
	this.urlHashMap["UniControlSystem:114:1670"] = "UniControlSystem.c:54,57,146,314,333&UniControlSystem.h:43,58,61";
	/* <S1>/Filter Coefficient */
	this.urlHashMap["UniControlSystem:114:1671"] = "UniControlSystem.c:45,145&UniControlSystem.h:49";
	/* <S1>/Integral Gain */
	this.urlHashMap["UniControlSystem:114:1667"] = "UniControlSystem.c:28,202&UniControlSystem.h:105";
	/* <S1>/Integrator */
	this.urlHashMap["UniControlSystem:114:1669"] = "UniControlSystem.c:48,51,154,311,330&UniControlSystem.h:42,52,55";
	/* <S1>/Proportional Gain */
	this.urlHashMap["UniControlSystem:114:1666"] = "UniControlSystem.c:36,155&UniControlSystem.h:113";
	/* <S1>/Saturate */
	this.urlHashMap["UniControlSystem:114:1673"] = "UniControlSystem.c:24,32,160,172&UniControlSystem.h:101,109";
	/* <S1>/Sum */
	this.urlHashMap["UniControlSystem:114:1665"] = "UniControlSystem.c:153";
	/* <S1>/SumD */
	this.urlHashMap["UniControlSystem:114:1672"] = "UniControlSystem.c:148";
	/* <S1>/Switch */
	this.urlHashMap["UniControlSystem:114:1687"] = "UniControlSystem.c:298,309";
	/* <S2>/AND */
	this.urlHashMap["UniControlSystem:114:1686"] = "UniControlSystem.c:301";
	/* <S2>/DataTypeConv1 */
	this.urlHashMap["UniControlSystem:114:1678"] = "UniControlSystem.c:280,287";
	/* <S2>/DataTypeConv2 */
	this.urlHashMap["UniControlSystem:114:1679"] = "UniControlSystem.c:300";
	/* <S2>/DeadZone */
	this.urlHashMap["UniControlSystem:114:1681"] = "UniControlSystem.c:25,33,177,186&UniControlSystem.h:102,110";
	/* <S2>/Equal */
	this.urlHashMap["UniControlSystem:114:1685"] = "UniControlSystem.c:302";
	/* <S2>/NotEqual */
	this.urlHashMap["UniControlSystem:114:1683"] = "UniControlSystem.c:188";
	/* <S2>/SignDeltaU */
	this.urlHashMap["UniControlSystem:114:1682"] = "UniControlSystem.c:191,200";
	/* <S2>/SignPreIntegrator */
	this.urlHashMap["UniControlSystem:114:1684"] = "UniControlSystem.c:289,303";
	/* <S2>/ZeroGain */
	this.urlHashMap["UniControlSystem:114:1680"] = "UniControlSystem.c:60,174&UniControlSystem.h:64";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "UniControlSystem"};
	this.sidHashMap["UniControlSystem"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "UniControlSystem:114"};
	this.sidHashMap["UniControlSystem:114"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "UniControlSystem:114:1674"};
	this.sidHashMap["UniControlSystem:114:1674"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<Root>/In1"] = {sid: "UniControlSystem:1"};
	this.sidHashMap["UniControlSystem:1"] = {rtwname: "<Root>/In1"};
	this.rtwnameHashMap["<Root>/In2"] = {sid: "UniControlSystem:22"};
	this.sidHashMap["UniControlSystem:22"] = {rtwname: "<Root>/In2"};
	this.rtwnameHashMap["<Root>/In3"] = {sid: "UniControlSystem:23"};
	this.sidHashMap["UniControlSystem:23"] = {rtwname: "<Root>/In3"};
	this.rtwnameHashMap["<Root>/In4"] = {sid: "UniControlSystem:24"};
	this.sidHashMap["UniControlSystem:24"] = {rtwname: "<Root>/In4"};
	this.rtwnameHashMap["<Root>/In5"] = {sid: "UniControlSystem:25"};
	this.sidHashMap["UniControlSystem:25"] = {rtwname: "<Root>/In5"};
	this.rtwnameHashMap["<Root>/In6"] = {sid: "UniControlSystem:26"};
	this.sidHashMap["UniControlSystem:26"] = {rtwname: "<Root>/In6"};
	this.rtwnameHashMap["<Root>/In7"] = {sid: "UniControlSystem:27"};
	this.sidHashMap["UniControlSystem:27"] = {rtwname: "<Root>/In7"};
	this.rtwnameHashMap["<Root>/In8"] = {sid: "UniControlSystem:28"};
	this.sidHashMap["UniControlSystem:28"] = {rtwname: "<Root>/In8"};
	this.rtwnameHashMap["<Root>/In9"] = {sid: "UniControlSystem:42"};
	this.sidHashMap["UniControlSystem:42"] = {rtwname: "<Root>/In9"};
	this.rtwnameHashMap["<Root>/In10"] = {sid: "UniControlSystem:43"};
	this.sidHashMap["UniControlSystem:43"] = {rtwname: "<Root>/In10"};
	this.rtwnameHashMap["<Root>/In11"] = {sid: "UniControlSystem:44"};
	this.sidHashMap["UniControlSystem:44"] = {rtwname: "<Root>/In11"};
	this.rtwnameHashMap["<Root>/In12"] = {sid: "UniControlSystem:45"};
	this.sidHashMap["UniControlSystem:45"] = {rtwname: "<Root>/In12"};
	this.rtwnameHashMap["<Root>/In13"] = {sid: "UniControlSystem:58"};
	this.sidHashMap["UniControlSystem:58"] = {rtwname: "<Root>/In13"};
	this.rtwnameHashMap["<Root>/In14"] = {sid: "UniControlSystem:59"};
	this.sidHashMap["UniControlSystem:59"] = {rtwname: "<Root>/In14"};
	this.rtwnameHashMap["<Root>/In15"] = {sid: "UniControlSystem:60"};
	this.sidHashMap["UniControlSystem:60"] = {rtwname: "<Root>/In15"};
	this.rtwnameHashMap["<Root>/In16"] = {sid: "UniControlSystem:61"};
	this.sidHashMap["UniControlSystem:61"] = {rtwname: "<Root>/In16"};
	this.rtwnameHashMap["<Root>/Constant"] = {sid: "UniControlSystem:81"};
	this.sidHashMap["UniControlSystem:81"] = {rtwname: "<Root>/Constant"};
	this.rtwnameHashMap["<Root>/Constant1"] = {sid: "UniControlSystem:110"};
	this.sidHashMap["UniControlSystem:110"] = {rtwname: "<Root>/Constant1"};
	this.rtwnameHashMap["<Root>/PID1 "] = {sid: "UniControlSystem:114"};
	this.sidHashMap["UniControlSystem:114"] = {rtwname: "<Root>/PID1 "};
	this.rtwnameHashMap["<Root>/Sub1 "] = {sid: "UniControlSystem:113"};
	this.sidHashMap["UniControlSystem:113"] = {rtwname: "<Root>/Sub1 "};
	this.rtwnameHashMap["<Root>/Terminator1"] = {sid: "UniControlSystem:119"};
	this.sidHashMap["UniControlSystem:119"] = {rtwname: "<Root>/Terminator1"};
	this.rtwnameHashMap["<Root>/Terminator10"] = {sid: "UniControlSystem:49"};
	this.sidHashMap["UniControlSystem:49"] = {rtwname: "<Root>/Terminator10"};
	this.rtwnameHashMap["<Root>/Terminator11"] = {sid: "UniControlSystem:62"};
	this.sidHashMap["UniControlSystem:62"] = {rtwname: "<Root>/Terminator11"};
	this.rtwnameHashMap["<Root>/Terminator12"] = {sid: "UniControlSystem:63"};
	this.sidHashMap["UniControlSystem:63"] = {rtwname: "<Root>/Terminator12"};
	this.rtwnameHashMap["<Root>/Terminator13"] = {sid: "UniControlSystem:64"};
	this.sidHashMap["UniControlSystem:64"] = {rtwname: "<Root>/Terminator13"};
	this.rtwnameHashMap["<Root>/Terminator14"] = {sid: "UniControlSystem:65"};
	this.sidHashMap["UniControlSystem:65"] = {rtwname: "<Root>/Terminator14"};
	this.rtwnameHashMap["<Root>/Terminator15"] = {sid: "UniControlSystem:109"};
	this.sidHashMap["UniControlSystem:109"] = {rtwname: "<Root>/Terminator15"};
	this.rtwnameHashMap["<Root>/Terminator2"] = {sid: "UniControlSystem:105"};
	this.sidHashMap["UniControlSystem:105"] = {rtwname: "<Root>/Terminator2"};
	this.rtwnameHashMap["<Root>/Terminator3"] = {sid: "UniControlSystem:106"};
	this.sidHashMap["UniControlSystem:106"] = {rtwname: "<Root>/Terminator3"};
	this.rtwnameHashMap["<Root>/Terminator4"] = {sid: "UniControlSystem:107"};
	this.sidHashMap["UniControlSystem:107"] = {rtwname: "<Root>/Terminator4"};
	this.rtwnameHashMap["<Root>/Terminator5"] = {sid: "UniControlSystem:108"};
	this.sidHashMap["UniControlSystem:108"] = {rtwname: "<Root>/Terminator5"};
	this.rtwnameHashMap["<Root>/Terminator6"] = {sid: "UniControlSystem:41"};
	this.sidHashMap["UniControlSystem:41"] = {rtwname: "<Root>/Terminator6"};
	this.rtwnameHashMap["<Root>/Terminator7"] = {sid: "UniControlSystem:46"};
	this.sidHashMap["UniControlSystem:46"] = {rtwname: "<Root>/Terminator7"};
	this.rtwnameHashMap["<Root>/Terminator8"] = {sid: "UniControlSystem:47"};
	this.sidHashMap["UniControlSystem:47"] = {rtwname: "<Root>/Terminator8"};
	this.rtwnameHashMap["<Root>/Terminator9"] = {sid: "UniControlSystem:48"};
	this.sidHashMap["UniControlSystem:48"] = {rtwname: "<Root>/Terminator9"};
	this.rtwnameHashMap["<Root>/Out1"] = {sid: "UniControlSystem:9"};
	this.sidHashMap["UniControlSystem:9"] = {rtwname: "<Root>/Out1"};
	this.rtwnameHashMap["<Root>/Out2"] = {sid: "UniControlSystem:10"};
	this.sidHashMap["UniControlSystem:10"] = {rtwname: "<Root>/Out2"};
	this.rtwnameHashMap["<Root>/Out3"] = {sid: "UniControlSystem:11"};
	this.sidHashMap["UniControlSystem:11"] = {rtwname: "<Root>/Out3"};
	this.rtwnameHashMap["<Root>/Out4"] = {sid: "UniControlSystem:12"};
	this.sidHashMap["UniControlSystem:12"] = {rtwname: "<Root>/Out4"};
	this.rtwnameHashMap["<Root>/Out5"] = {sid: "UniControlSystem:13"};
	this.sidHashMap["UniControlSystem:13"] = {rtwname: "<Root>/Out5"};
	this.rtwnameHashMap["<Root>/Out6"] = {sid: "UniControlSystem:14"};
	this.sidHashMap["UniControlSystem:14"] = {rtwname: "<Root>/Out6"};
	this.rtwnameHashMap["<Root>/Out7"] = {sid: "UniControlSystem:15"};
	this.sidHashMap["UniControlSystem:15"] = {rtwname: "<Root>/Out7"};
	this.rtwnameHashMap["<Root>/Out8"] = {sid: "UniControlSystem:16"};
	this.sidHashMap["UniControlSystem:16"] = {rtwname: "<Root>/Out8"};
	this.rtwnameHashMap["<Root>/Out9"] = {sid: "UniControlSystem:66"};
	this.sidHashMap["UniControlSystem:66"] = {rtwname: "<Root>/Out9"};
	this.rtwnameHashMap["<Root>/Out10"] = {sid: "UniControlSystem:67"};
	this.sidHashMap["UniControlSystem:67"] = {rtwname: "<Root>/Out10"};
	this.rtwnameHashMap["<Root>/Out11"] = {sid: "UniControlSystem:68"};
	this.sidHashMap["UniControlSystem:68"] = {rtwname: "<Root>/Out11"};
	this.rtwnameHashMap["<Root>/Out12"] = {sid: "UniControlSystem:69"};
	this.sidHashMap["UniControlSystem:69"] = {rtwname: "<Root>/Out12"};
	this.rtwnameHashMap["<Root>/Out13"] = {sid: "UniControlSystem:70"};
	this.sidHashMap["UniControlSystem:70"] = {rtwname: "<Root>/Out13"};
	this.rtwnameHashMap["<Root>/Out14"] = {sid: "UniControlSystem:71"};
	this.sidHashMap["UniControlSystem:71"] = {rtwname: "<Root>/Out14"};
	this.rtwnameHashMap["<Root>/Out15"] = {sid: "UniControlSystem:72"};
	this.sidHashMap["UniControlSystem:72"] = {rtwname: "<Root>/Out15"};
	this.rtwnameHashMap["<Root>/Out16"] = {sid: "UniControlSystem:73"};
	this.sidHashMap["UniControlSystem:73"] = {rtwname: "<Root>/Out16"};
	this.rtwnameHashMap["<S1>/u"] = {sid: "UniControlSystem:114:1"};
	this.sidHashMap["UniControlSystem:114:1"] = {rtwname: "<S1>/u"};
	this.rtwnameHashMap["<S1>/Clamping circuit"] = {sid: "UniControlSystem:114:1674"};
	this.sidHashMap["UniControlSystem:114:1674"] = {rtwname: "<S1>/Clamping circuit"};
	this.rtwnameHashMap["<S1>/Constant"] = {sid: "UniControlSystem:114:1688"};
	this.sidHashMap["UniControlSystem:114:1688"] = {rtwname: "<S1>/Constant"};
	this.rtwnameHashMap["<S1>/Derivative Gain"] = {sid: "UniControlSystem:114:1668"};
	this.sidHashMap["UniControlSystem:114:1668"] = {rtwname: "<S1>/Derivative Gain"};
	this.rtwnameHashMap["<S1>/Filter"] = {sid: "UniControlSystem:114:1670"};
	this.sidHashMap["UniControlSystem:114:1670"] = {rtwname: "<S1>/Filter"};
	this.rtwnameHashMap["<S1>/Filter Coefficient"] = {sid: "UniControlSystem:114:1671"};
	this.sidHashMap["UniControlSystem:114:1671"] = {rtwname: "<S1>/Filter Coefficient"};
	this.rtwnameHashMap["<S1>/Integral Gain"] = {sid: "UniControlSystem:114:1667"};
	this.sidHashMap["UniControlSystem:114:1667"] = {rtwname: "<S1>/Integral Gain"};
	this.rtwnameHashMap["<S1>/Integrator"] = {sid: "UniControlSystem:114:1669"};
	this.sidHashMap["UniControlSystem:114:1669"] = {rtwname: "<S1>/Integrator"};
	this.rtwnameHashMap["<S1>/Proportional Gain"] = {sid: "UniControlSystem:114:1666"};
	this.sidHashMap["UniControlSystem:114:1666"] = {rtwname: "<S1>/Proportional Gain"};
	this.rtwnameHashMap["<S1>/Saturate"] = {sid: "UniControlSystem:114:1673"};
	this.sidHashMap["UniControlSystem:114:1673"] = {rtwname: "<S1>/Saturate"};
	this.rtwnameHashMap["<S1>/Sum"] = {sid: "UniControlSystem:114:1665"};
	this.sidHashMap["UniControlSystem:114:1665"] = {rtwname: "<S1>/Sum"};
	this.rtwnameHashMap["<S1>/SumD"] = {sid: "UniControlSystem:114:1672"};
	this.sidHashMap["UniControlSystem:114:1672"] = {rtwname: "<S1>/SumD"};
	this.rtwnameHashMap["<S1>/Switch"] = {sid: "UniControlSystem:114:1687"};
	this.sidHashMap["UniControlSystem:114:1687"] = {rtwname: "<S1>/Switch"};
	this.rtwnameHashMap["<S1>/y"] = {sid: "UniControlSystem:114:10"};
	this.sidHashMap["UniControlSystem:114:10"] = {rtwname: "<S1>/y"};
	this.rtwnameHashMap["<S2>/preSat"] = {sid: "UniControlSystem:114:1675"};
	this.sidHashMap["UniControlSystem:114:1675"] = {rtwname: "<S2>/preSat"};
	this.rtwnameHashMap["<S2>/preIntegrator"] = {sid: "UniControlSystem:114:1676"};
	this.sidHashMap["UniControlSystem:114:1676"] = {rtwname: "<S2>/preIntegrator"};
	this.rtwnameHashMap["<S2>/AND"] = {sid: "UniControlSystem:114:1686"};
	this.sidHashMap["UniControlSystem:114:1686"] = {rtwname: "<S2>/AND"};
	this.rtwnameHashMap["<S2>/DataTypeConv1"] = {sid: "UniControlSystem:114:1678"};
	this.sidHashMap["UniControlSystem:114:1678"] = {rtwname: "<S2>/DataTypeConv1"};
	this.rtwnameHashMap["<S2>/DataTypeConv2"] = {sid: "UniControlSystem:114:1679"};
	this.sidHashMap["UniControlSystem:114:1679"] = {rtwname: "<S2>/DataTypeConv2"};
	this.rtwnameHashMap["<S2>/DeadZone"] = {sid: "UniControlSystem:114:1681"};
	this.sidHashMap["UniControlSystem:114:1681"] = {rtwname: "<S2>/DeadZone"};
	this.rtwnameHashMap["<S2>/Equal"] = {sid: "UniControlSystem:114:1685"};
	this.sidHashMap["UniControlSystem:114:1685"] = {rtwname: "<S2>/Equal"};
	this.rtwnameHashMap["<S2>/NotEqual"] = {sid: "UniControlSystem:114:1683"};
	this.sidHashMap["UniControlSystem:114:1683"] = {rtwname: "<S2>/NotEqual"};
	this.rtwnameHashMap["<S2>/SignDeltaU"] = {sid: "UniControlSystem:114:1682"};
	this.sidHashMap["UniControlSystem:114:1682"] = {rtwname: "<S2>/SignDeltaU"};
	this.rtwnameHashMap["<S2>/SignPreIntegrator"] = {sid: "UniControlSystem:114:1684"};
	this.sidHashMap["UniControlSystem:114:1684"] = {rtwname: "<S2>/SignPreIntegrator"};
	this.rtwnameHashMap["<S2>/ZeroGain"] = {sid: "UniControlSystem:114:1680"};
	this.sidHashMap["UniControlSystem:114:1680"] = {rtwname: "<S2>/ZeroGain"};
	this.rtwnameHashMap["<S2>/Clamp"] = {sid: "UniControlSystem:114:1677"};
	this.sidHashMap["UniControlSystem:114:1677"] = {rtwname: "<S2>/Clamp"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
