#pragma once
#include <QStringList>
#include <QMap>
/*
	This OptionIdentity namespace declares some enum constants to mark the
options of the option list. Each enum constant represents a child item of
the root item "option".
	Almost all of the primary items get an unique number constant to show its
indentity. And the following two information can be read from the identity number:
	1. the parent item.
	2. the type of data the children item should have.
*/
typedef QMap<QString, int> CommandSet;
typedef QList<CommandSet> CommandSetList;
namespace OptionIdentity
{
	/*
	The following statements shows how to read the information:
	1. the first digit of the number tells the type of data this item should be given.
		1----string			|		4----array				|		7----number/array
		2----number			|		5----object				|		8----string/boolean
		3----boolean		|		6----number/string		|		9----boolean/array
		for example: int str=10001/10000=1.	str means a string.
	2. the rest digits tells which item is the parent item.
		for example: int rest=(10049%10000)/50=0.	rest's parent item is "title".
		more detials are in the array "itemArray".
	*/
	const QStringList PrimaryItemArray = { "title","legend","grid","xAxis","polar","radiusAxis","angleAxis",
		"radar","dataZoom","dataZoom","visualMap","visualMap","tooltip","axisPointer","toolbox","brush","geo",
		"parallel","parallelAxis","singleAxis","timeline","calendar","dataset","aria","series","series",
		"series" ,"series" ,"textStyle" ,"option","yAxis","grid3D","xAxis3D","yAxis3D","zAxis3D"};
	const QStringList SecondaryItemArray = { " ","id","show","text","link","target","textStyle","subText","subLink","subTarget","subTextStyle","textAlign",
		"textVerticalAlign","triggerEvent","padding","itemGap","zlevel","z","left","top","right","bottom","backgroundColor","borderColor","borderWidth",
		"borderRadius","shadowBlur","shadowColor","shadowOffsetX","shadowOffsetY",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"type","id","show","zlevel","z","left","top","right","bottom","width","height","orient","align","padding","itemGap","itemWidth",
		"itemHeight","symbolKeepAspect","formatter","selectedMode","inactiveColor","selected","textStyle","tooltip","data","backgroundColor","borderColor",
		"borderWidth","borderRadius","shadowBlur","shadowColor","shadowOffsetX","shadowOffectY","scrollDataIndex","pageButtonItemGap","pageButtonGap",
		"pageButtonPosition","pageFormatter","pageIcons","pageIconColor","pageIconInactiveColor","pageIconSize","pageTextStyle","animation",
		"animationDurationUpdate"," "," "," "," "," ","id","show","zlevel","z","left","top","right","bottom","width","height","containLabel","backgroundColor",
		"borderColor","borderWidth","shadowBlur","shadowColor","shadowOffsetX","shadowOffsetY","tooltip",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"id","show"," ","gridIndex","position","offset","type","name","nameLocation","nameTextStyle","nameGap","nameRotate","inverse","boundaryGap","min","max",
		"scale","splitNumber","minInterval","maxInterval","interval","logBase",
		"silent","triggerEvent","axisLine","axisTick","axisLabel","splitLine","splitArea","data","axisPointer","zlevel","z",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"id","zlevel","z","center","radius","tooltip",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"id","polarIndex","type","name","nameLocation","nameTextStyle","nameGap","nameRotate","inverse","boundaryGap","min","max","scale","splitNumber","minInterval","maxInterval","interval",
		"logBase","silent","triggerEvent",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"id","polarIndex","startAngle","clockWise","type","boundaryGap","min","max","scale","splitNumber","minInterval","maxInterval","interval","logBase",
		"silent","triggerEvent","axisLine","axisTick","axisLabel","splitLine","splitArea","data","axisPointer","zlevel","z",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"id","zlevel","z","center","radius","startAngle","name","nameGap","splitNumber",
		"shape","scale","silent","triggerEvent","axisLine","splitLine","splitArea","indicator",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"type","id","disabled","xAxisIndex","yAxisIndex","radiusAxisIndex",
		"angleAxisIndex","filterMode","start","end","startValue","endValue","minSpan","maxSpan","minValueSpan","maxValueSpan","orient","zoomLock",
		"throttle","rangeMode","zoomOnMouseWheel","moveOnMouseMove","moveOnMouseWheel","preventDefaultMouseMove","show","backgroundColor","dataBackground",
		"fillerColor","borderColor","handleIcon","handleSize","handleStyle","labelPrecision","labelFormatter","showDetail","showDataShadow","realtime",
		"textStyle",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"type","id","splitNumber","pieces",
		"categories","min","max","minOpen","maxOpen","selectedMode","inverse","precision","itemWidth","itemHeight","align","text","textGap","showLabel",
		"itemGap","itemSymbol","show","dimension","seriesIndex","hoverLink","inRange","outOutRange","controller","zlevel","z","left","top","right","bottom",
		"orient","padding","backgroundColor","borderColor","borderWidth","color","textStyle","formatter","range","calculable","realtime"," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," ","show","trigger","axisPointer","showContent","alwaysShowContent","triggerOn","showDelay",
		"hideDelay","enterable","renderMode","confine","transitionDuration","position","formatter","backgroundColor","borderColor","borderWidth","padding",
		"textStyle","extraCssText"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"id","show","type","snap","z","label","lineStyle","shadowStyle","triggerTooltip","value","status","handle","link","triggerOn"," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","id","show","orient",
		"itemSize","itemGap","showTitle","feature","iconStyle","emphasis","zlevel","z","left","top","right","bottom","width","height"," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","id","toolbox","brushLink","seriesIndex",
		"geoIndex","xAxisIndex","yAxisIndex","brushType","brushMode","transformable","brushStyle","throttleType","throttleDelay","removeOnClick","inBrush",
		"outOfBrush","z"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"id","show","map","roam","center","aspectScale","boundingCoords","zoom","scaleLimit","nameMap","selectedMode","label","itemStyle","emphasis","zlevel",
		"z","left","top","right","bottom","layoutCenter","layoutSize","regions","silent"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," ","id","zlevel","z","left","top","right","bottom","width","height","layout","axisExpandable","axisExpandCenter",
		"axisExpandCount","axisExpandWidth","axisExpandTriggerOn","parallelAxisDefault"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","id","dim","parallelIndex","realtime","areaSelectStyle","type","name",
		"nameLocation","nameTextStyle","nameGap","nameRotate","inverse","boundaryGap","min","max","scale","splitNumber","minInterval","maxInterval",
		"interval","logBase","silent","triggerEvent","axisLine","axisTick","axisLabel","data"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," ","id","zlevel","z","left","top","right","bottom","width","height","orient","type","name","nameLocation","nameTextStyle",
		"nameGap","nameRotate","inverse","boundaryGap","min","max","scale","splitNumber","minInterval","maxInterval","interval","logBase","silent",
		"triggerEvent","axisLine","axisTick","axisLabel","splitLine","splitArea","data","axisPointer","tooltip"," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," ","show","type","axisType","currentIndex","autoPlay","rewind","loop","playInterval","realtime","controlPosition","zlevel","z","left","top",
		"right","bottom","padding","orient","inverse","symbol","symbolSize","symbolRotate","symbolKeepAspect","symbolOffset","lineStyle","label","itemStyle",
		"checkpointStyle","controlStyle","emphasis","data"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","id","zlevel","z",
		"left","top","right","bottom","width","height","range","cellSize","orient","splitLine","itemStyle","dayLabel","monthLabel","yearLabel","silent"," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","id","source","dimension",
		"sourceHeader"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," ","show","description","general","series","data"," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","type","id",
		"name","coordinateSystem","xAxisIndex","yAxisIndex","polarIndex","symbol","symbolSize","symbolRotate","symbolKeepAspect","symbolOffset","showSymbol",
		"showAllSymbol","hoverAnimation","legendHoverLink","stack","cursor","connectNulls","clipOverflow","step","label","itemStyle","lineStyle","areaStyle",
		"emphasis","smooth","smoothMonotone","sampling","dimensions","encode","seriesLayoutBy","datasetIndex","data","markPoint","markLink","markLine",
		"markArea","zlevel","z","silent","animation","animationThreshold","animationDuration","animationEasing","animationDelay","animationDurationUpdate",
		"animationEasingUpdate","animationDelayUpdate","tooltip","barWidth","barMaxWidth","barMinHeight","barGap","barCategoryGap","large","largeThreshold",
		"progressive","progressiveThreshold","progressiveChunkMode","hoverOffset","selectedMode","selectedOffset","clockWise","startAngle","minAngle",
		"minShowLabelAngle","roseType","avoidLabelOverlap","stillShowZeroSum","center","radius","geoIndex","calendarIndex","effectType","showEffectOn",
		"rippleEffect","radarIndex","left","top","right","bottom","width","height","layout","orient","roam","expandAndCollapse","initialTreeDepth","leaves",
		"squareRatio","leafDepth","drillDownIcon","nodeClick","zoomToNodeRatio","visualDimension","visualMin","visualMax","colorAlpha","colorSaturation",
		"colorMappingBy","visibleMin","childrenVisibleMin","upperLabel","breadcrumb","highlightPolicy","sort","renderLabelForZeroData","highlight","downplay",
		"levels","boxWidth","barMinWidth","blurSize","minOpacity","maxOpacity","map","aspectScale","boundingCoords","zoom","scaleLimit","nameMap",
		"layoutCenter","layoutSize","mapValueCalculation","showLegendSymbol","parallelIndex","inactiveOpactive","activeOpactive","realtime","polyline",
		"circular","force","nodeScaleRatio","draggable","focusNodeAdjacency","edgeSymbol","edgeSymbolSize","edgeLabel","categories","nodes","links","edges",
		"nodeWidth","nodeGap","nodeAlign","layoutIterations","min","max","minSize","maxSize","gap","funnelAlign","labelLine","endAngle","pointer","detail",
		"title","boundaryGap","singleAxisIndex"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," ","color","fontStyle","fontWeight","fontFamily","fontSize","lineHeight","width","height",
		"textBorderColor","textBorderWidth","textShadowColor","textShadowBlur","textOffsetX","textOffsetY"," "," "," "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","title","legend","grid","xAxis","yAxis","polar",
		"radiusAxis","angleAxis","radar","dataZoom","visualMap","tooltip","axisPointer","toolbox","brush","geo","parallel","parallelAxis","singleAxis",
		"timeline","graphic","calendar","dataset","aria","series","color","backgroundColor","textStyle","animation","animationThreshold","animationDuration",
		"animationEasing","animationDelay","animationDurationUpdate","animationEasingUpdate","animationDelayUpdate","blendMode","hoverLayerThreshold",
		"useUTC"," "," "," "," "," "," "," "," "," "," "," ","id","show","gridIndex","position","offset","type","name","nameLocation","nameTextStyle",
		"nameGap","nameRotate","inverse","boundaryGap","min","max","scale","splitNumber","minInterval","maxInterval","interval","logBase","silent",
		"triggerEvent","axisLine","axisTick","axisLabel","splitLine","splitArea","data","axisPointer","zlevel","z",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"show","boxWidth","boxHeight","boxDepth","axisLine","axisLabel","axisTick","splitLine","splitArea","axisPointer","enviroment","light","postEffect",
		"temporalSuperSampling","viewControl","zlevel","left","top","bottom","width","height",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"show","name","grid3Dindex","nameTextStyle","nameGap","type","min","max","scale","splitNumber","minInterval","logBase","data","axisLine","axisLabel",
		"axisTick","splitLine","splitArea","axisPointer",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"show","name","grid3Dindex","nameTextStyle","nameGap","type","min","max","scale","splitNumber","minInterval","logBase","data","axisLine","axisLabel",
		"axisTick","splitLine","splitArea","axisPointer",
		" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",
		"show","name","grid3Dindex","nameTextStyle","nameGap","type","min","max","scale","splitNumber","minInterval","logBase","data","axisLine","axisLabel",
		"axisTick","splitLine","splitArea","axisPointer"
		};

	namespace title
	{
		//1 - 50
		enum title
		{
			id = 10001,
			show = 30002,
			text = 10003,
			link = 10004,
			target = 10005,
			textStyle = 50006,
			subText = 10007,
			subLink = 10008,
			subTarget = 10009,
			subTextStyle = 50010,
			textAlign = 10011,
			textVerticalAlign = 10012,
			triggerEvent = 30013,
			padding = 20014,
			itemGap = 20015,
			zlevel = 20016,
			z = 20017,
			left = 60018,
			top = 60019,
			right = 60020,
			bottom = 60021,
			backgroundColor = 10022,
			borderColor = 10023,
			borderWidth = 20024,
			borderRadius = 70025,
			shadowBlur = 20026,
			shadowColor = 10027,
			shadowOffsetX = 20028,
			shadowOffsetY = 20029,
		};
	}
	namespace legend {
		//51-100
		enum legend
		{
			type = 10051,
			id = 10052,
			show = 30053,
			zlevel = 20054,
			z = 20055,
			left = 60056,
			top = 60057,
			right = 60058,
			bottom = 60059,
			width = 60060,
			height = 60061,
			orient = 10062,
			align = 10063,
			padding = 20064,
			itemGap = 20065,
			itemWidth = 20066,
			itemHeight = 20067,
			symbolKeepAspect = 30068,
			formatter = 10069,
			selectedMode = 80070,
			inactiveColor = 10071,
			selected = 50072,
			textStyle = 50073,
			tooltip = 50074,
			data = 40075,
			backgroundColor = 10076,
			borderColor = 10077,
			borderWidth = 20078,
			borderRadius = 70079,
			shadowBlur = 20080,
			shadowColor = 10081,
			shadowOffsetX = 20082,
			shadowOffectY = 20083,
			scrollDataIndex = 20084,
			pageButtonItemGap = 20085,
			pageButtonGap = 20086,
			pageButtonPosition = 10087,
			pageFormatter = 10088,
			pageIcons = 50089,
			pageIconColor = 10090,
			pageIconInactiveColor = 10091,
			pageIconSize = 70092,
			pageTextStyle = 50093,
			animation = 30094,
			animationDurationUpdate = 20095
		};
	}
	namespace grid {
		//101-150
		enum grid
		{
			id = 10101,
			show = 30102,
			zlevel = 20103,
			z = 20104,
			left = 60105,
			top = 60106,
			right = 60107,
			bottom = 60108,
			width = 60109,
			height = 60110,
			containLabel = 30111,
			backgroundColor = 10112,
			borderColor = 10113,
			borderWidth = 20114,
			shadowBlur = 20115,
			shadowColor = 10116,
			shadowOffsetX = 20117,
			shadowOffsetY = 20118,
			tooltip = 50119
		};
	}
	namespace xAxis {
		//151-200
		enum xAxis
		{
			id = 10151,
			show = 30152,
			//one mistake here.
			gridIndex = 20154,
			position = 10155,
			offset = 20156,
			type = 10157,
			name = 10158,
			nameLocation = 10159,
			nameTextStyle = 50160,
			nameGap = 20161,
			nameRotate = 20162,
			inverse = 30163,
			boundaryGap = 90164,
			min = 60165,
			max = 60166,
			scale = 30167,
			splitNumber = 20168,
			minInterval = 20169,
			maxInterval = 20170,
			interval = 20171,
			logBase = 20172,
			silent = 30173,
			triggerEvent = 30174,
			axisLine = 50175,
			axisTick = 50176,
			axisLabel = 50177,
			splitLine = 50178,
			splitArea = 50179,
			data = 40180,
			axisPointer = 50181,
			zlevel = 20182,
			z = 20183,
		};
	}
	namespace polar {
		//201-250
		enum polar
		{
			id = 10201,
			zlevel = 20202,
			z = 20203,
			center = 40204,
			radius = 60205,
			tooltip = 50206,
		};
	}
	namespace radiusAxis {
		//251-300
		enum radiusAxis
		{
			id = 10251,
			polarIndex = 20252,
			type = 10253,
			name = 10254,
			nameLocation = 10255,
			nameTextStyle = 50256,
			nameGap = 20257,
			nameRotate = 20258,
			inverse = 30259,
			boundaryGap = 90260,
			min = 60261,
			max = 60262,
			scale = 30263,
			splitNumber = 20264,
			minInterval = 20265,
			maxInterval = 20266,
			interval = 20267,
			logBase = 20268,
			silent = 30269,
			triggerEvent = 30270,
		};
	}
	namespace angleAxis {
		//301-350
		enum angleAxis
		{
			id = 10301,
			polarIndex = 20302,
			startAngle = 20303,
			clockWise = 30304,
			type = 10305,
			boundaryGap = 90306,
			min = 60307,
			max = 60308,
			scale = 30309,
			splitNumber = 20310,
			minInterval = 20311,
			maxInterval = 20312,
			interval = 20313,
			logBase = 20314,
			silent = 30315,
			triggerEvent = 30316,
			axisLine = 50317,
			axisTick = 50318,
			axisLabel = 50319,
			splitLine = 50320,
			splitArea = 50321,
			data = 40322,
			axisPointer = 50323,
			zlevel = 20324,
			z = 20325
		};
	}
	namespace radar {
		//351-400
		enum radar
		{
			id = 10351,
			zlevel = 20352,
			z = 20353,
			center = 40354,
			radius = 60355,
			startAngle = 20356,
			name = 50357,
			nameGap = 20358,
			splitNumber = 20359,
			shape = 10360,
			scale = 30361,
			silent = 30362,
			triggerEvent = 30363,
			axisLine = 50364,
			splitLine = 50365,
			splitArea = 50366,
			indicator = 40367,
		};
	}
	namespace dataZoom {
		//401-500
		enum dataZoom
		{
			type = 10401,
			id = 10402,
			disabled = 30403,
			xAxisIndex = 60404,
			yAxisIndex = 60405,
			radiusAxisIndex = 60406,
			angleAxisIndex = 60407,
			filterMode = 10408,
			start = 20409,
			end = 20410,
			startValue = 60411,
			endValue = 60412,
			minSpan = 20413,
			maxSpan = 20414,
			minValueSpan = 60415,
			maxValueSpan = 60416,
			orient = 10417,
			zoomLock = 30418,
			throttle = 20419,
			rangeMode = 40420,
			zoomOnMouseWheel = 30421,
			moveOnMouseMove = 30422,
			moveOnMouseWheel = 30423,
			preventDefaultMouseMove = 30424,
			//slider
			show = 30425,
			backgroundColor = 10426,
			dataBackground = 50427,
			fillerColor = 10428,
			borderColor = 10429,
			handleIcon = 10430,
			handleSize = 60431,
			handleStyle = 50432,
			labelPrecision = 60433,
			labelFormatter = 10434,
			showDetail = 30435,
			showDataShadow = 10436,
			realtime = 30437,
			textStyle = 50438,
		};
	}
	namespace visualMap {
		//501-600
		enum visualMap
		{
			type = 10501,
			id = 10502,
			splitNumber = 20503,
			pieces = 40504,
			categories = 40505,
			min = 20506,
			max = 20507,
			minOpen = 30508,
			maxOpen = 30509,
			selectedMode = 10510,
			inverse = 30511,
			precision = 20512,
			itemWidth = 20513,
			itemHeight = 20514,
			align = 10515,
			text = 40516,
			textGap = 40517,
			showLabel = 30518,
			itemGap = 20519,
			itemSymbol = 10520,
			show = 30521,
			dimension = 20522,
			seriesIndex = 70523,
			hoverLink = 30524,
			inRange = 50525,
			outOutRange = 50526,
			controller = 50527,
			zlevel = 20528,
			z = 20529,
			left = 60530,
			top = 60531,
			right = 60532,
			bottom = 60533,
			orient = 10534,
			padding = 70535,
			backgroundColor = 10536,
			borderColor = 10537,
			borderWidth = 20538,
			color = 40539,
			textStyle = 50540,
			formatter = 10541,
			//continuous
			range = 40542,
			calculable = 30543,
			realtime = 30544,
		};
	}
	namespace tooltip {
		//601-650
		enum tooltip
		{
			show = 30601,
			trigger = 10602,
			axisPointer = 50603,
			showContent = 30604,
			alwaysShowContent = 30605,
			triggerOn = 10606,
			showDelay = 20607,
			hideDelay = 20608,
			enterable = 30609,
			renderMode = 10610,
			confine = 30611,
			transitionDuration = 20612,
			position = 40613,
			formatter = 10614,
			backgroundColor = 10615,
			borderColor = 10616,
			borderWidth = 20617,
			padding = 20618,
			textStyle = 50619,
			extraCssText = 10620,
		};
	}
	namespace axisPointer {
		//651-700
		enum axisPointer
		{
			id = 10651,
			show = 30652,
			type = 10653,
			snap = 30654,
			z = 20655,
			label = 50656,
			lineStyle = 50657,
			shadowStyle = 50658,
			triggerTooltip = 30659,
			value = 20660,
			status = 10661,
			handle = 50662,
			link = 40663,
			triggerOn = 10664,
		};
	}
	namespace toolBox {
		//701-750
		enum toolBox
		{
			id = 10701,
			show = 30702,
			orient = 10703,
			itemSize = 20704,
			itemGap = 20705,
			showTitle = 30706,
			feature = 50707,
			iconStyle = 50708,
			emphasis = 50709,
			zlevel = 20710,
			z = 20711,
			left = 60712,
			top = 60713,
			right = 60714,
			bottom = 60715,
			width = 60716,
			height = 60717,
		};
	}
	namespace brush {
		//751-800
		enum brush
		{
			id = 10751,
			toolbox = 40752,
			brushLink = 40753,
			seriesIndex = 40754,
			geoIndex = 40755,
			xAxisIndex = 40756,
			yAxisIndex = 40757,
			brushType = 10758,
			brushMode = 10759,
			transformable = 30760,
			brushStyle = 50761,
			throttleType = 10762,
			throttleDelay = 20763,
			removeOnClick = 20764,
			inBrush = 50765,
			outOfBrush = 50766,
			z = 20767,
		};
	}
	namespace geo {
		//801-850
		enum geo
		{
			id = 10801,
			show = 30802,
			map = 10803,
			roam = 80804,
			center = 40805,
			aspectScale = 20806,
			boundingCoords = 40807,
			zoom = 20808,
			scaleLimit = 50809,
			nameMap = 50810,
			selectedMode = 80811,
			label = 50812,
			itemStyle = 50813,
			emphasis = 50814,
			zlevel = 20815,
			z = 20816,
			left = 60817,
			top = 60818,
			right = 60819,
			bottom = 60820,
			layoutCenter = 40821,
			layoutSize = 60822,
			regions = 40823,
			silent = 30824,
		};
	}
	namespace parallel {
		//851-900
		enum parallel
		{
			id = 10851,
			zlevel = 20852,
			z = 20853,
			left = 60854,
			top = 60855,
			right = 60856,
			bottom = 60857,
			width = 60858,
			height = 60859,
			layout = 10860,
			axisExpandable = 30861,
			axisExpandCenter = 20862,
			axisExpandCount = 20863,
			axisExpandWidth = 20864,
			axisExpandTriggerOn = 10865,
			parallelAxisDefault = 50866,
		};
	}
	namespace parallelAxis {
		//901-950
		enum parallelAxis
		{
			id = 10901,
			dim = 20902,
			parallelIndex = 20903,
			realtime = 30904,
			areaSelectStyle = 50905,
			type = 10906,
			name = 10907,
			nameLocation = 10908,
			nameTextStyle = 50909,
			nameGap = 20910,
			nameRotate = 20911,
			inverse = 30912,
			boundaryGap = 90913,
			min = 60914,
			max = 60915,
			scale = 30916,
			splitNumber = 20917,
			minInterval = 20918,
			maxInterval = 20919,
			interval = 20920,
			logBase = 20921,
			silent = 30922,
			triggerEvent = 30923,
			axisLine = 50924,
			axisTick = 50925,
			axisLabel = 50926,
			data = 40927,
		};
	}
	namespace singleAxis {
		//951-1000
		enum singleAxis
		{
			id = 10951,
			zlevel = 20952,
			z = 20953,
			left = 60954,
			top = 60955,
			right = 60956,
			bottom = 60957,
			width = 60958,
			height = 60959,
			orient = 10960,
			type = 10961,
			name = 10962,
			nameLocation = 10963,
			nameTextStyle = 50964,
			nameGap = 20965,
			nameRotate = 20966,
			inverse = 30967,
			boundaryGap = 90968,
			min = 60969,
			max = 60970,
			scale = 30971,
			splitNumber = 20972,
			minInterval = 20973,
			maxInterval = 20974,
			interval = 20975,
			logBase = 20976,
			silent = 30977,
			triggerEvent = 30978,
			axisLine = 50979,
			axisTick = 50980,
			axisLabel = 50981,
			splitLine = 50982,
			splitArea = 50983,
			data = 40984,
			axisPointer = 50985,
			tooltip = 50986,
		};
	}
	namespace timeline {
		//1001-1050
		enum timeline
		{
			show = 31001,
			type = 11002,
			axisType = 11003,
			currentIndex = 21004,
			autoPlay = 31005,
			rewind = 31006,
			loop = 31007,
			playInterval = 21008,
			realtime = 31009,
			controlPosition = 11010,
			zlevel = 21011,
			z = 21012,
			left = 61013,
			top = 61014,
			right = 61015,
			bottom = 61016,
			padding = 71017,
			orient = 11018,
			inverse = 31019,
			symbol = 11020,
			symbolSize = 71021,
			symbolRotate = 21022,
			symbolKeepAspect = 31023,
			symbolOffset = 41024,
			lineStyle = 51025,
			label = 51026,
			itemStyle = 51027,
			checkpointStyle = 51028,
			controlStyle = 51029,
			emphasis = 51030,
			data = 41031,
		};
	}
	namespace calender {
		//1051-1100
		enum calender
		{
			id = 11051,
			zlevel = 21052,
			z = 21053,
			left = 61054,
			top = 61055,
			right = 61056,
			bottom = 61057,
			width = 61058,
			height = 61059,
			range = 41060,
			cellSize = 71061,
			orient = 11062,
			splitLine = 51063,
			itemStyle = 51064,
			dayLabel = 51065,
			monthLabel = 51066,
			yearLabel = 51067,
			silent = 31068,
		};
	}
	namespace dataset {
		//1101-1150
		enum dataset
		{
			id = 11101,
			source = 41102,
			dimension = 41103,
			sourceHeader = 31104,
		};
	}
	namespace aria {
		//1151-1200
		enum aria
		{
			show = 11151,
			description = 11152,
			general = 51153,
			series = 51154,
			data = 51155,
		};
	}
	namespace series {
		//1201-1400
		enum series
		{
			//line
			type = 11201,
			id = 11202,
			name = 11203,
			coordinateSystem = 11204,
			xAxisIndex = 21205,
			yAxisIndex = 21206,
			polarIndex = 21207,
			symbol = 11208,
			symbolSize = 71209,
			symbolRotate = 21210,
			symbolKeepAspect = 31211,
			symbolOffset = 41212,
			showSymbol = 31213,
			showAllSymbol = 81214,
			hoverAnimation = 31215,
			legendHoverLink = 31216,
			stack = 11217,
			cursor = 11218,
			connectNulls = 31219,
			clipOverflow = 31220,
			step = 81221,
			label = 51222,
			itemStyle = 51223,
			lineStyle = 51224,
			areaStyle = 51225,
			emphasis = 51226,
			smooth = 21227,
			smoothMonotone = 11228,
			sampling = 11229,
			dimensions = 41230,
			encode = 51231,
			seriesLayoutBy = 11232,
			datasetIndex = 21233,
			data = 41234,
			markPoint = 51235,
			markLink = 51236,
			markLine = 51237,
			markArea = 51238,
			zlevel = 21239,
			z = 21240,
			silent = 31241,
			animation = 31242,
			animationThreshold = 21243,
			animationDuration = 21244,
			animationEasing = 11245,
			animationDelay = 21246,
			animationDurationUpdate = 21247,
			animationEasingUpdate = 11248,
			animationDelayUpdate = 21249,
			tooltip = 51250,
			//bar
			barWidth = 61251,
			barMaxWidth = 61252,
			barMinHeight = 21253,
			barGap = 11254,
			barCategoryGap = 11255,
			large = 31256,
			largeThreshold = 21257,
			progressive = 21258,
			progressiveThreshold = 21259,
			progressiveChunkMode = 11260,
			//pie
			hoverOffset = 21261,
			selectedMode = 31262,
			selectedOffset = 21263,
			clockWise = 31264,
			startAngle = 21265,
			minAngle = 21266,
			minShowLabelAngle = 21267,
			roseType = 81268,
			avoidLabelOverlap = 31269,
			stillShowZeroSum = 31270,
			center = 41271,
			radius = 41272,
			//scatter
			geoIndex = 21273,
			calendarIndex = 21274,
			//effctscatter
			effectType = 11275,
			showEffectOn = 11276,
			rippleEffect = 51277,
			//radar
			radarIndex = 21278,
			//tree
			left = 61279,
			top = 61280,
			right = 61281,
			bottom = 61282,
			width = 61283,
			height = 61284,
			layout = 11285,
			orient = 11286,
			roam = 81287,
			expandAndCollapse = 31288,
			initialTreeDepth = 21289,
			leaves = 51290,
			//treemap
			squareRatio = 21291,
			leafDepth = 21292,
			drillDownIcon = 11293,
			nodeClick = 81294,
			zoomToNodeRatio = 21295,
			visualDimension = 21296,
			visualMin = 21297,
			visualMax = 21298,
			colorAlpha = 41299,
			colorSaturation = 21300,
			colorMappingBy = 11301,
			visibleMin = 21302,
			childrenVisibleMin = 21303,
			upperLabel = 51304,
			breadcrumb = 51305,
			//sunburst
			highlightPolicy = 11306,
			sort = 11307,
			renderLabelForZeroData = 31308,
			highlight = 51309,
			downplay = 51310,
			levels = 41311,
			//boxplot
			boxWidth = 41312,
			//candlestick
			barMinWidth = 61313,
			//heatmap
			blurSize = 21314,
			minOpacity = 21315,
			maxOpacity = 21316,
			//map
			map = 11317,
			aspectScale = 21318,
			boundingCoords = 41319,
			zoom = 21320,
			scaleLimit = 51321,
			nameMap = 51322,
			layoutCenter = 41323,
			layoutSize = 61324,
			mapValueCalculation = 11325,
			showLegendSymbol = 31326,
			//parallel
			parallelIndex = 21327,
			inactiveOpactive = 21328,
			activeOpactive = 21329,
			realtime = 31330,
			//lines
			polyline = 31331,
			//graph
			circular = 51332,
			force = 51333,
			nodeScaleRatio = 21334,
			draggable = 31335,
			focusNodeAdjacency = 31336,
			edgeSymbol = 41337,
			edgeSymbolSize = 71338,
			edgeLabel = 51339,
			categories = 41340,
			nodes = 41341,
			links = 41342,
			edges = 41343,
			//sankey
			nodeWidth = 21344,
			nodeGap = 21345,
			nodeAlign = 11346,
			layoutIterations = 21347,
			//funnel
			min = 21348,
			max = 21349,
			minSize = 61350,
			maxSize = 61351,
			gap = 21352,
			funnelAlign = 11353,
			labelLine = 51354,
			//gauge
			endAngle = 21355,
			pointer = 51356,
			detail = 51357,
			title = 51358,
			//themeRiver
			boundaryGap = 41359,
			singleAxisIndex = 21360,
			//scatter3D
			grid3DIndex = 21361,
			geo3DIndex = 21362,
			globe3DIndex = 21363,
			blendMode = 11364,
			//bar3D
			bevelSize = 21365,
			bevelSmoothness = 21366,
			shading = 11367,
			realisticMaterial = 51368,
			lambertMaterial = 51369,
			colorMaterial = 51370,
			//surface
			equation = 51371,
			parametricEquation = 51372,
			//flowGL
			particleDensity = 21373,
			particleType = 11374,
			particleSize = 21375,
			particleSpeed = 21376,
			particleTrail = 21377,
			supersampling = 21378,
			gridWidth = 61379,
			gridHeight = 61380,
		};
	}
	namespace textStyle {
		//1401-1450
		enum textStyle
		{
			color = 11401,
			fontStyle = 11402,
			fontWeight = 61403,
			fontFamily = 11404,
			fontSize = 21405,
			lineHeight = 21406,
			width = 61407,
			height = 61408,
			textBorderColor = 11409,
			textBorderWidth = 21410,
			textShadowColor = 11411,
			textShadowBlur = 21412,
			textOffsetX = 21413,
			textOffsetY = 21414,
		};
	}
	namespace option {
		//1451-1500
		enum option
		{
			title = 41451,
			legend = 41452,
			grid = 41453,
			xAxis = 41454,
			polar = 41455,
			radiusAxis = 41456,
			angleAxis = 41457,
			radar = 41458,
			dataZoom = 41460,
			visualMap = 41462,
			tooltip = 41463,
			axisPointer = 41464,
			toolbox = 41465,
			brush = 41466,
			geo = 41467,
			parallel = 41468,
			parallelAxis = 41469,
			singleAxis = 41470,
			timeline = 41471,
			//graphic = 41471,
			calendar = 41472,
			dataset = 41473,
			aria = 41474,
			series = 41478,
			//color = 41476,
			//backgroundColor = 11477,
			textStyle = 51479,
			//animation = 31479,
			//animationThreshold = 21480,
			//animationDuration = 21481,
			//animationEasing = 11482,
			//animationDelay = 21483,
			//animationDurationUpdate = 21484,
			//animationEasingUpdate = 11485,
			//animationDelayUpdate = 21486,
			//blendMode = 11487,
			//hoverLayerThreshold = 21488,
			//useUTC = 31489,
			yAxis = 41481,
			grid3D = 41482,
			xAxis3D = 41483,
			yAxis3D = 41484,
			zAxis3D = 41485
		};
	}
	namespace yAxis {
		//1501-1550
		enum yAxis
		{
			id = 11501,
			show = 31502,
			//one mistake here.
			gridIndex = 21503,
			position = 11504,
			offset = 21505,
			type = 11506,
			name = 11507,
			nameLocation = 11508,
			nameTextStyle = 51509,
			nameGap = 21510,
			nameRotate = 21511,
			inverse = 31512,
			boundaryGap = 91513,
			min = 61514,
			max = 61515,
			scale = 31516,
			splitNumber = 21517,
			minInterval = 21518,
			maxInterval = 21519,
			interval = 21520,
			logBase = 21521,
			silent = 31522,
			triggerEvent = 31523,
			axisLine = 51524,
			axisTick = 51525,
			axisLabel = 51526,
			splitLine = 51527,
			splitArea = 51528,
			data = 41529,
			axisPointer = 51530,
			zlevel = 21531,
			z = 21532,
		};
	}
	namespace grid3D {
		//1551-1600
		enum grid3D {
			show = 31551,
			boxWidth = 21552,
			boxHeight = 21553,
			boxDepth = 21554,
			axisLine = 51555,
			axisLabel = 51556,
			axisTick = 51557,
			splitLine = 51558,
			splitArea = 51559,
			axisPointer = 51560,
			enviroment = 11561,
			light = 51562,
			postEffect = 51563,
			temporalSuperSampling = 51564,
			viewControl = 51565,
			zlevel = 21566,
			left = 61567,
			top = 61568,
			bottom = 61569,
			width = 61570,
			height = 61571
		};
	}
	namespace xAxis3D {
		//1601-1650
		enum xAxis3D {
			show=31601,
			name=11602,
			grid3Dindex=21603,
			nameTextStyle=51604,
			nameGap=21605,
			type=11606,
			min=61607,
			max=61608,
			scale=31609,
			splitNumber=21610,
			minInterval=21611,
			logBase=21612,
			data=41613,
			axisLine=51614,
			axisLabel=51615,
			axisTick=51616,
			splitLine=51617,
			splitArea=51618,
			axisPointer=51619
		};
	}
	namespace yAxis3D {
		//1651-1700
		enum yAxis {
			show = 31651,
			name = 11652,
			grid3Dindex = 21653,
			nameTextStyle = 51654,
			nameGap = 21655,
			type = 11656,
			min = 61657,
			max = 61658,
			scale = 31659,
			splitNumber = 21660,
			minInterval = 21661,
			logBase = 21662,
			data = 41663,
			axisLine = 51664,
			axisLabel = 51665,
			axisTick = 51666,
			splitLine = 51667,
			splitArea = 51668,
			axisPointer = 51669
		};
	}
	namespace zAxis3D {
		//1701-1750
		enum zAxis3D {
			show = 31701,
			name = 11702,
			grid3Dindex = 21703,
			nameTextStyle = 51704,
			nameGap = 21705,
			type = 11706,
			min = 61707,
			max = 61708,
			scale = 31709,
			splitNumber = 21710,
			minInterval = 21711,
			logBase = 21712,
			data = 41713,
			axisLine = 51714,
			axisLabel = 51715,
			axisTick = 51716,
			splitLine = 51717,
			splitArea = 51718,
			axisPointer = 51719
		};
	}
}

namespace CommandLineSet
{
	const CommandSet systemCommand = {
		{"cls",0},{"exit",1},{"set",2},{"get",3},{"clear",4},{"",3},{"setFont",5},{"setFontSize",6},
		{"plot",7},{"setTheme",8}
	};

	enum SystemCommand
	{
		EmptyCommand = -2,
		ErrorCommand = -1,
		Cls = 0,
		Exit = 1,
		Set = 2,
		Get = 3,
		Clear = 4,
		SetFont = 5,
		setFontSize = 6,
		Plot = 7,
		setTheme=8,
	};

	const CommandSet topLayerCommand = {
		{"title",41451},{"legend",41452},{"grid",41453},
		{"xAxis",41454},{"polar",41455},{"radiusAxis",41456},{"angleAxis",41457},
		{"radar",41458},{"dataZoom",41460},{"visualMap",41462},{"tooltip",41463},{"axisPointer",41464},
		{"toolbox",41465},{"brush",41466},{"geo",41467},{"parallel",41468},{"parallelAxis",41469},
		{"singleAxis",41470},{"timeline",41471}/*,{"graphic",41471}*/,{"calendar",41472},{"dataset",41473},
		{"aria",41474},{"series",41478}/*,{"color",41476},{"backgroundColor",11477}*/,{"textStyle",51479},
		/*{"animation",31479},{"animationThreshold",21480},{"animationDuration",21481},
		{"animationEasing",11482},{"animationDelay",21483},{"animationDurationUpdate",21484},
		{"animationEasingUpdate",11485},{"animationDelayUpdate",21486},{"blendMode",11487},
		{"hoverLayerThreshold",21488},{"useUTC",31489},*/{"yAxis",41481},{"grid3D",41482},{"xAxis3D",41483},
		{"yAxis3D",41484},{"zAxis3D",41485}
	};

	const CommandSet commandsOfTitle = { 
		{"id",10001},{"show",30002},{"text",10003},
		{"link",10004},{"target",10005},{"textStyle",50006},{"subText",10007},{"subLink",10008},
		{"subTarget",10009},{"subTextStyle",50010},{"textAlign",10011},{"textVerticalAlign",10012},
		{"triggerEvent",30013},{"padding",20014},{"itemGap",20015},{"zlevel",20016},{"z",20017},
		{"left",60018},{"top",60019},{"right",60020},{"bottom",60021},{"backgroundColor",10022},
		{"borderColor",10023},{"borderWidth",20024},{"borderRadius",70025},{"shadowBlur",20026},
		{"shadowColor",10027},{"shadowOffsetX",20028},{"shadowOffsetY",20029} 
	};

	const CommandSet commandsOfLegend = { 
		{"type",10051},{"id",10052},{"show",30053},{"zlevel",20054},
		{"z",20055},{"left",60056},{"top",60057},{"right",60058},{"bottom",60059},{"width",60060},
		{"height",60061},{"orient",10062},{"align",10063},{"padding",20064},{"itemGap",20065},
		{"itemWidth",20066},{"itemHeight",20067},{"symbolKeepAspect",30068},{"formatter",10069},
		{"selectedMode",80070},{"inactiveColor",10071},{"selected",50072},{"textStyle",50073},
		{"tooltip",50074},{"data",40075},{"backgroundColor",10076},{"borderColor",10077},
		{"borderWidth",20078},{"borderRadius",70079},{"shadowBlur",20080},{"shadowColor",10081},
		{"shadowOffsetX",20082},{"shadowOffectY",20083},{"scrollDataIndex",20084},
		{"pageButtonItemGap",20085},{"pageButtonGap",20086},{"pageButtonPosition",10087},
		{"pageFormatter",10088},{"pageIcons",50089},{"pageIconColor",10090},{"pageIconInactiveColor",10091},
		{"pageIconSize",70092},{"pageTextStyle",50093},{"animation",30094},{"animationDurationUpdate",20095} 
	};

	const CommandSet commandsOfGrid = { 
		{"id",10101},{"show",30102},{"zlevel",20103},{"z",20104},
		{"left",60105},{"top",60106},{"right",60107},{"bottom",60108},{"width",60109},{"height",60110},
		{"containLabel",30111},{"backgroundColor",10112},{"borderColor",10113},{"borderWidth",20114},
		{"shadowBlur",20115},{"shadowColor",10116},{"shadowOffsetX",20117},{"shadowOffsetY",20118},
		{"tooltip",50119} 
	};

	const CommandSet commandsOfxAxis = { 
		{"id",10151},{"show",30152},{"gridIndex",20154},
		{"position",10155},{"offset",20156},{"type",10157},{"name",10158},{"nameLocation",10159},
		{"nameTextStyle",50160},{"nameGap",20161},{"nameRotate",20162},{"inverse",30163},
		{"boundaryGap",90164},{"min",60165},{"max",60166},{"scale",30167},{"splitNumber",20168},
		{"minInterval",20169},{"maxInterval",20170},{"interval",20171},{"logBase",20172},{"silent",30173},
		{"triggerEvent",30174},{"axisLine",50175},{"axisTick",50176},{"axisLabel",50177},{"splitLine",50178},
		{"splitArea",50179},{"data",40180},{"axisPointer",50181},{"zlevel",20182},{"z",20183} 
	};

	const CommandSet commandsOfPolar = { 
		{"id",10201},{"zlevel",20202},{"z",20203},{"center",40204},
		{"radius",60205},{"tooltip",50206} 
	};

	const CommandSet commandsOfRadiusAxis = { 
		{"id",10251},{"polarIndex",20252},{"type",10253},
		{"name",10254},{"nameLocation",10255},{"nameTextStyle",50256},{"nameGap",20257},{"nameRotate",20258},
		{"inverse",30259},{"boundaryGap",90260},{"min",60261},{"max",60262},{"scale",30263},
		{"splitNumber",20264},{"minInterval",20265},{"maxInterval",20266},{"interval",20267},
		{"logBase",20268},{"silent",30269},{"triggerEvent",30270} 
	};

	const CommandSet commandsOfAngleAxis = { 
		{"id",10301},{"polarIndex",20302},{"startAngle",20303},
		{"clockWise",30304},{"type",10305},{"boundaryGap",90306},{"min",60307},{"max",60308},{"scale",30309},
		{"splitNumber",20310},{"minInterval",20311},{"maxInterval",20312},{"interval",20313},
		{"logBase",20314},{"silent",30315},{"triggerEvent",30316},{"axisLine",50317},{"axisTick",50318},
		{"axisLabel",50319},{"splitLine",50320},{"splitArea",50321},{"data",40322},{"axisPointer",50323},
		{"zlevel",20324},{"z",20325} 
	};

	const CommandSet commandsOfRadar = { 
		{"id",10351},{"zlevel",20352},{"z",20353},{"center",40354},
		{"radius",60355},{"startAngle",20356},{"name",50357},{"nameGap",20358},{"splitNumber",20359},
		{"shape",10360},{"scale",30361},{"silent",30362},{"triggerEvent",30363},{"axisLine",50364},
		{"splitLine",50365},{"splitArea",50366},{"indicator",40367} 
	};

	const CommandSet commandsOfDataZoom = { 
		{"type",10401},{"id",10402},{"disabled",30403},
		{"xAxisIndex",60404},{"yAxisIndex",60405},{"radiusAxisIndex",60406},{"angleAxisIndex",60407},
		{"filterMode",10408},{"start",20409},{"end",20410},{"startValue",60411},{"endValue",60412},
		{"minSpan",20413},{"maxSpan",20414},{"minValueSpan",60415},{"maxValueSpan",60416},{"orient",10417},
		{"zoomLock",30418},{"throttle",20419},{"rangeMode",40420},{"zoomOnMouseWheel",30421},
		{"moveOnMouseMove",30422},{"moveOnMouseWheel",30423},{"preventDefaultMouseMove",30424},
		{"show",30425},{"backgroundColor",10426},{"dataBackground",50427},{"fillerColor",10428},
		{"borderColor",10429},{"handleIcon",10430},{"handleSize",60431},{"handleStyle",50432},
		{"labelPrecision",60433},{"labelFormatter",10434},{"showDetail",30435},{"showDataShadow",10436},
		{"realtime",30437},{"textStyle",50438} 
	};

	const CommandSet commandsOfVisualMap = { 
		{"type",10501},{"id",10502},{"splitNumber",20503},
		{"pieces",40504},{"categories",40505},{"min",20506},{"max",20507},{"minOpen",30508},
		{"maxOpen",30509},{"selectedMode",10510},{"inverse",30511},{"precision",20512},{"itemWidth",20513},
		{"itemHeight",20514},{"align",10515},{"text",40516},{"textGap",40517},{"showLabel",30518},
		{"itemGap",20519},{"itemSymbol",10520},{"show",30521},{"dimension",20522},{"seriesIndex",70523},
		{"hoverLink",30524},{"inRange",50525},{"outOutRange",50526},{"controller",50527},{"zlevel",20528},
		{"z",20529},{"left",60530},{"top",60531},{"right",60532},{"bottom",60533},{"orient",10534},
		{"padding",70535},{"backgroundColor",10536},{"borderColor",10537},{"borderWidth",20538},
		{"color",40539},{"textStyle",50540},{"formatter",10541},{"//continuous",40542},{"calculable",30543},
		{"realtime",30544} 
	};

	const CommandSet commandsOfToolTip = { 
		{"show",30601},{"trigger",10602},{"axisPointer",50603},
		{"showContent",30604},{"alwaysShowContent",30605},{"triggerOn",10606},{"showDelay",20607},
		{"hideDelay",20608},{"enterable",30609},{"renderMode",10610},{"confine",30611},
		{"transitionDuration",20612},{"position",40613},{"formatter",10614},{"backgroundColor",10615},
		{"borderColor",10616},{"borderWidth",20617},{"padding",20618},{"textStyle",50619},
		{"extraCssText",10620} 
	};

	const CommandSet commandsOfAxisPointer = { 
		{"id",10651},{"show",30652},{"type",10653},
		{"snap",30654},{"z",20655},{"label",50656},{"lineStyle",50657},{"shadowStyle",50658},
		{"triggerTooltip",30659},{"value",20660},{"status",10661},{"handle",50662},{"link",40663},
		{"triggerOn",10664} 
	};

	const CommandSet commandsOfToolBox = { 
		{"id",10701},{"show",30702},{"orient",10703},
		{"itemSize",20704},{"itemGap",20705},{"showTitle",30706},{"feature",50707},{"iconStyle",50708},
		{"emphasis",50709},{"zlevel",20710},{"z",20711},{"left",60712},{"top",60713},{"right",60714},
		{"bottom",60715},{"width",60716},{"height",60717} 
	};

	const CommandSet commandsOfBrush = { 
		{"id",10751},{"toolbox",40752},{"brushLink",40753},
		{"seriesIndex",40754},{"geoIndex",40755},{"xAxisIndex",40756},{"yAxisIndex",40757},
		{"brushType",10758},{"brushMode",10759},{"transformable",30760},{"brushStyle",50761},
		{"throttleType",10762},{"throttleDelay",20763},{"removeOnClick",20764},{"inBrush",50765},
		{"outOfBrush",50766},{"z",20767} 
	};

	const CommandSet commandsOfGeo = { 
		{"id",10801},{"show",30802},{"map",10803},{"roam",80804},
		{"center",40805},{"aspectScale",20806},{"boundingCoords",40807},{"zoom",20808},{"scaleLimit",50809},
		{"nameMap",50810},{"selectedMode",80811},{"label",50812},{"itemStyle",50813},{"emphasis",50814},
		{"zlevel",20815},{"z",20816},{"left",60817},{"top",60818},{"right",60819},{"bottom",60820},
		{"layoutCenter",40821},{"layoutSize",60822},{"regions",40823},{"silent",30824} 
	};

	const CommandSet commandsOfParallel = { 
		{"id",10851},{"zlevel",20852},{"z",20853},{"left",60854},
		{"top",60855},{"right",60856},{"bottom",60857},{"width",60858},{"height",60859},{"layout",10860},
		{"axisExpandable",30861},{"axisExpandCenter",20862},{"axisExpandCount",20863},
		{"axisExpandWidth",20864},{"axisExpandTriggerOn",10865},{"parallelAxisDefault",50866} 
	};

	const CommandSet commandsOfParallelAxis = { 
		{"id",10901},{"dim",20902},{"parallelIndex",20903},
		{"realtime",30904},{"areaSelectStyle",50905},{"type",10906},{"name",10907},{"nameLocation",10908},
		{"nameTextStyle",50909},{"nameGap",20910},{"nameRotate",20911},{"inverse",30912},
		{"boundaryGap",90913},{"min",60914},{"max",60915},{"scale",30916},{"splitNumber",20917},
		{"minInterval",20918},{"maxInterval",20919},{"interval",20920},{"logBase",20921},{"silent",30922},
		{"triggerEvent",30923},{"axisLine",50924},{"axisTick",50925},{"axisLabel",50926},{"data",40927} 
	};

	const CommandSet commandsOfSingleAxis = { 
		{"id",10951},{"zlevel",20952},{"z",20953},{"left",60954},
		{"top",60955},{"right",60956},{"bottom",60957},{"width",60958},{"height",60959},{"orient",10960},
		{"type",10961},{"name",10962},{"nameLocation",10963},{"nameTextStyle",50964},{"nameGap",20965},
		{"nameRotate",20966},{"inverse",30967},{"boundaryGap",90968},{"min",60969},{"max",60970},
		{"scale",30971},{"splitNumber",20972},{"minInterval",20973},{"maxInterval",20974},{"interval",20975},
		{"logBase",20976},{"silent",30977},{"triggerEvent",30978},{"axisLine",50979},{"axisTick",50980},
		{"axisLabel",50981},{"splitLine",50982},{"splitArea",50983},{"data",40984},{"axisPointer",50985},
		{"tooltip",50986} 
	};

	const CommandSet commandsOfTimeLine = { 
		{"show",31001},{"type",11002},{"axisType",11003},
		{"currentIndex",21004},{"autoPlay",31005},{"rewind",31006},{"loop",31007},{"playInterval",21008},
		{"realtime",31009},{"controlPosition",11010},{"zlevel",21011},{"z",21012},{"left",61013},
		{"top",61014},{"right",61015},{"bottom",61016},{"padding",71017},{"orient",11018},{"inverse",31019},
		{"symbol",11020},{"symbolSize",71021},{"symbolRotate",21022},{"symbolKeepAspect",31023},
		{"symbolOffset",41024},{"lineStyle",51025},{"label",51026},{"itemStyle",51027},
		{"checkpointStyle",51028},{"controlStyle",51029},{"emphasis",51030},{"data",41031} 
	};

	const CommandSet commandsOfGraphic = {};

	const CommandSet commandsOfCalender = { 
		{"id",11051},{"zlevel",21052},{"z",21053},{"left",61054},
		{"top",61055},{"right",61056},{"bottom",61057},{"width",61058},{"height",61059},{"range",41060},
		{"cellSize",71061},{"orient",11062},{"splitLine",51063},{"itemStyle",51064},{"dayLabel",51065},
		{"monthLabel",51066},{"yearLabel",51067},{"silent",31068} 
	};

	const CommandSet commandsOfDataSet = { 
		{"id",11101},{"source",41102},{"dimension",41103},
		{"sourceHeader",31104} 
	};

	const CommandSet commandsOfAria = { 
		{"show",11151},{"description",11152},{"general",51153},
		{"series",51154},{"data",51155} 
	};

	const CommandSet commandsOfSeries = { 
		{"type",11201},{"id",11202},{"name",11203},
		{"coordinateSystem",11204},{"xAxisIndex",21205},{"yAxisIndex",21206},{"polarIndex",21207},
		{"symbol",11208},{"symbolSize",71209},{"symbolRotate",21210},{"symbolKeepAspect",31211},
		{"symbolOffset",41212},{"showSymbol",31213},{"showAllSymbol",81214},{"hoverAnimation",31215},
		{"legendHoverLink",31216},{"stack",11217},{"cursor",11218},{"connectNulls",31219},
		{"clipOverflow",31220},{"step",81221},{"label",51222},{"itemStyle",51223},{"lineStyle",51224},
		{"areaStyle",51225},{"emphasis",51226},{"smooth",21227},{"smoothMonotone",11228},{"sampling",11229},
		{"dimensions",41230},{"encode",51231},{"seriesLayoutBy",11232},{"datasetIndex",21233},{"data",41234},
		{"markPoint",51235},{"markLink",51236},{"markLine",51237},{"markArea",51238},{"zlevel",21239},
		{"z",21240},{"silent",31241},{"animation",31242},{"animationThreshold",21243},
		{"animationDuration",21244},{"animationEasing",11245},{"animationDelay",21246},
		{"animationDurationUpdate",21247},{"animationEasingUpdate",11248},{"animationDelayUpdate",21249},
		{"tooltip",51250},{"barWidth",61251},{"barMaxWidth",61252},{"barMinHeight",21253},{"barGap",11254},
		{"barCategoryGap",11255},{"large",31256},{"largeThreshold",21257},{"progressive",21258},
		{"progressiveThreshold",21259},{"progressiveChunkMode",11260},{"hoverOffset",21261},
		{"selectedMode",31262},{"selectedOffset",21263},{"clockWise",31264},{"startAngle",21265},
		{"minAngle",21266},{"minShowLabelAngle",21267},{"roseType",81268},{"avoidLabelOverlap",31269},
		{"stillShowZeroSum",31270},{"center",41271},{"radius",41272},{"geoIndex",21273},
		{"calendarIndex",21274},{"effectType",11275},{"showEffectOn",11276},{"rippleEffect",51277},
		{"radarIndex",21278},{"left",61279},{"top",61280},{"right",61281},{"bottom",61282},{"width",61283},
		{"height",61284},{"layout",11285},{"orient",11286},{"roam",81287},{"expandAndCollapse",31288},
		{"initialTreeDepth",21289},{"leaves",51290},{"squareRatio",21291},{"leafDepth",21292},
		{"drillDownIcon",11293},{"nodeClick",81294},{"zoomToNodeRatio",21295},{"visualDimension",21296},
		{"visualMin",21297},{"visualMax",21298},{"colorAlpha",41299},{"colorSaturation",21300},
		{"colorMappingBy",11301},{"visibleMin",21302},{"childrenVisibleMin",21303},{"upperLabel",51304},
		{"breadcrumb",51305},{"highlightPolicy",11306},{"sort",11307},{"renderLabelForZeroData",31308},
		{"highlight",51309},{"downplay",51310},{"levels",41311},{"boxWidth",41312},{"barMinWidth",61313},
		{"blurSize",21314},{"minOpacity",21315},{"maxOpacity",21316},{"map",11317},{"aspectScale",21318},
		{"boundingCoords",41319},{"zoom",21320},{"scaleLimit",51321},{"nameMap",51322},
		{"layoutCenter",41323},{"layoutSize",61324},{"mapValueCalculation",11325},{"showLegendSymbol",31326},
		{"parallelIndex",21327},{"inactiveOpactive",21328},{"activeOpactive",21329},{"realtime",31330},
		{"polyline",31331},{"circular",51332},{"force",51333},{"nodeScaleRatio",21334},{"draggable",31335},
		{"focusNodeAdjacency",31336},{"edgeSymbol",41337},{"edgeSymbolSize",71338},{"edgeLabel",51339},
		{"categories",41340},{"nodes",41341},{"links",41342},{"edges",41343},{"nodeWidth",21344},
		{"nodeGap",21345},{"nodeAlign",11346},{"layoutIterations",21347},{"min",21348},{"max",21349},
		{"minSize",61350},{"maxSize",61351},{"gap",21352},{"funnelAlign",11353},{"labelLine",51354},
		{"endAngle",21355},{"pointer",51356},{"detail",51357},{"title",51358},{"boundaryGap",41359},
		{"singleAxisIndex",21360},{"grid3DIndex",21361},{"geo3DIndex",21362},{"globe3DIndex",21363},
		{"blendMode",11364},{"bevelSize",21365},{"bevelSmoothness",21366},{"shading",11367},
		{"realisticMaterial",51368},{"lambertMaterial",51369},{"colorMaterial",51370},{"equation",51371},
		{"parametricEquation",51372},{"particleDensity",21373},{"particleType",11374},{"particleSize",21375},
		{"particleSpeed",21376},{"particleTrail",21377},{"supersampling",21378},{"gridWidth",61379},{"gridHeight",61380}
	};

	const CommandSet commandsOfyAxis = { 
		{"id",11501},{"show",31502},{"gridIndex",21503},
		{"position",11504},{"offset",21505},{"type",11506},{"name",11507},{"nameLocation",11508},
		{"nameTextStyle",51509},{"nameGap",21510},{"nameRotate",21511},{"inverse",31512},
		{"boundaryGap",91513},{"min",61514},{"max",61515},{"scale",31516},{"splitNumber",21517},
		{"minInterval",21518},{"maxInterval",21519},{"interval",21520},{"logBase",21521},{"silent",31522},
		{"triggerEvent",31523},{"axisLine",51524},{"axisTick",51525},{"axisLabel",51526},{"splitLine",51527},
		{"splitArea",51528},{"data",41529},{"axisPointer",51530},{"zlevel",21531},{"z",21532} 
	};

	const CommandSet commandsOfGrid3D={
		{"show",31551},{"boxWidth",21552},{"boxHeight",21553},{"boxDepth",21554},{"axisLine",51555},
		{"axisLabel",51556},{"axisTick",51557},{"splitLine",51558},{"splitArea",51559},{"axisPointer",51560},
		{"enviroment",11561},{"light",51562},{"postEffect",51563},{"temporalSuperSampling",51564},
		{"viewControl",51565},{"zlevel",21566},{"left",61567},{"top",61568},{"bottom",61569},{"width",61570},{"height",61571}
	};

	const CommandSet commandsOfxAxis3D={
		{"show",31601},{"name",11602},{"grid3Dindex",21603},{"nameTextStyle",51604},{"nameGap",21605},{"type",11606},
		{"min",61607},{"max",61608},{"scale",31609},{"splitNumber",21610},{"minInterval",21611},{"logBase",21612},
		{"data",41613},{"axisLine",51614},{"axisLabel",51615},{"axisTick",51616},{"splitLine",51617},{"splitArea",51618},{"axisPointer",51619}
	};

	const CommandSet commandsOfyAxis3D={
		{"show",31601},{"name",11602},{"grid3Dindex",21603},{"nameTextStyle",51604},{"nameGap",21605},
		{"type",11606},{"min",61607},{"max",61608},{"scale",31609},{"splitNumber",21610},{"minInterval",21611},
		{"logBase",21612},{"data",41613},{"axisLine",51614},{"axisLabel",51615},{"axisTick",51616},{"splitLine",51617},
		{"splitArea",51618},{"axisPointer",51619}
	};

	const CommandSet commandsOfzAxis3D={
		{"show",31701},{"name",11702},{"grid3Dindex",21703},{"nameTextStyle",51704},{"nameGap",21705},{"type",11706},
		{"min",61707},{"max",61708},{"scale",31709},{"splitNumber",21710},{"minInterval",21711},{"logBase",21712},
		{"data",41713},{"axisLine",51714},{"axisLabel",51715},{"axisTick",51716},{"splitLine",51717},{"splitArea",51718},
		{"axisPointer",51719}
	};

	const CommandSet commandsOfColor = {};

	const CommandSet commandsOfBackgroundColor = {};

	const CommandSet commandsOfTextStyle = { 
		{"color",11401},{"fontStyle",11402},{"fontWeight",61403},
		{"fontFamily",11404},{"fontSize",21405},{"lineHeight",21406},{"width",61407},{"height",61408},
		{"textBorderColor",11409},{"textBorderWidth",21410},{"textShadowColor",11411},
		{"textShadowBlur",21412},{"textOffsetX",21413},{"textOffsetY",21414} 
	};

	const CommandSetList secondLayerCommand = {
		/*
			this list always stays the same order with the topLayerCommand.
		*/
		commandsOfTitle,
		commandsOfLegend,
		commandsOfGrid,
		commandsOfxAxis,
		commandsOfPolar,
		commandsOfRadiusAxis,
		commandsOfAngleAxis,
		commandsOfRadar,
		commandsOfDataZoom, commandsOfDataZoom,
		commandsOfVisualMap, commandsOfVisualMap,
		commandsOfToolTip,
		commandsOfAxisPointer,
		commandsOfToolBox,
		commandsOfBrush,
		commandsOfGeo,
		commandsOfParallel,
		commandsOfParallelAxis,
		commandsOfSingleAxis,
		commandsOfTimeLine,
		//commandsOfGraphic,
		commandsOfCalender,
		commandsOfDataSet,
		commandsOfAria,
		commandsOfSeries, commandsOfSeries, commandsOfSeries, commandsOfSeries,
		//commandsOfColor,
		//commandsOfBackgroundColor ,
		commandsOfTextStyle,
		commandsOfyAxis, commandsOfyAxis,
		commandsOfGrid3D,
		commandsOfxAxis3D,
		commandsOfyAxis3D,
		commandsOfzAxis3D
	};
}