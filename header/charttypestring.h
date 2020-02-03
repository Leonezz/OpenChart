#pragma once
#include <QString>
struct ChartType
{
	const QString Line = u8"折线图";
	const QString Bar = u8"柱状图";
	const QString Pie = u8"饼图";
	const QString Scatter = u8"散点图";
	const QString Map = u8"地理坐标图";
	const QString K = u8"K线图";
	const QString Radar = u8"雷达图";
	const QString HeatMap = u8"热力图";
	const QString BoxPlot = u8"盒须图";
	const QString Relation = u8"关系图";
	const QString Tree = u8"树图";
	const QString RectangleTree = u8"矩形树图";
	const QString Sun = u8"旭日图";
	const QString ParallelCoordinateSystem = u8"平行坐标系";
	const QString Sankey = u8"桑基图";
	const QString Funnel = u8"漏斗图";
	const QString DashBoard = u8"仪表盘";
	const QString River = u8"主题河流图";
	const QString Calendar = u8"日历坐标图";
	const QString DataSet = u8"数据集";
	const QString D3Bar = u8"3D柱状图";
	const QString D3Scatter = u8"3D散点图";
	const QString D3Surface = u8"3D曲面图";
	const QString D3Map = u8"3D地图";
	const QString D3Line = u8"3D折线图";
}; 
#pragma execution_character_set("utf-8")	//set char-set to utf-8