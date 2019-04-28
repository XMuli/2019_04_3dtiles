#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "QtCore/QJsonDocument"
#include "QtCore/QJsonParseError"
#include "QtCore/QFile"
#include "QtCore/QJsonObject"
#include "QtCore/QDebug"
#include "QtCore/QJsonArray"
#include "QtCore/QString"

#pragma comment(lib,"C:/Qt/Qt5.9.7/5.9.7/msvc2015_64/lib/Qt5Core.lib")

using namespace std;


class MY_QT_JSON
{
public:
	MY_QT_JSON();
	MY_QT_JSON(string str);
	virtual ~MY_QT_JSON();

	//dispay
	void myJsonDisplay();	

	//Modify
	bool myQtJsonModify();   //进行修改

	void myJsonOutStr(string& str);  //将修改好的JSON格式，替换输出参数str


private:

	QJsonObject m_rootObj;  //该Json对象 实际操作
	QStringList m_rootKeys;

};

