#include "MY_QT_JSON.h"



MY_QT_JSON::MY_QT_JSON()
{
	//cout << "MY_QT_JSON::MY_QT_JSON() BEGIN//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

	QFile loadFile("../../json/json_out.json");

	if (!loadFile.open(QIODevice::ReadOnly))
	{
		qDebug() << "could't open projects json";
		return;
	}

	QByteArray allData = loadFile.readAll();
	loadFile.close();

	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

	if (json_error.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!";
		return;
	}
	m_rootObj = jsonDoc.object();

	//输出所有key，这一步是非必须的，放最后的话，你可能读不到任何key
	m_rootKeys = m_rootObj.keys();
	QJsonValue rootValue;

	for (int i = 0; i < m_rootKeys.size(); i++)
	{
		rootValue = m_rootObj.value(m_rootKeys.at(i));
	}

	//cout << "MY_QT_JSON::MY_QT_JSON() END//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl;

}


MY_QT_JSON::MY_QT_JSON(string str)   // string>>QString >> QJson 
{

	QString jsonString = QString::fromStdString(str);

	QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
	if (jsonDocument.isNull()) {
		qDebug() << "===> please check the string " << jsonString.toLocal8Bit().data();
	}
	m_rootObj = jsonDocument.object();

}

MY_QT_JSON::~MY_QT_JSON()
{
}



void MY_QT_JSON::myJsonDisplay()
{
	cout << "void MY_QT_JSON::myJsonDisplay() BEGIN//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	m_rootKeys = m_rootObj.keys();
	QJsonValue rootValue;

	for (int i = 0; i < m_rootKeys.size(); i++)
	{
		qDebug() << "key" << i << " is:" << m_rootKeys.at(i);
		rootValue = m_rootObj.value(m_rootKeys.at(i));
		qDebug() << "Value" << i << " is:" << rootValue << endl << endl;

	}

	cout << "void MY_QT_JSON::myJsonDisplay() BEGIN//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl<<endl<<endl;
}


bool MY_QT_JSON::myQtJsonModify()   //进行修改
{

#pragma region 优化版本
#pragma region step1
	//<step1>
	//1gltf.extensionsRequired.splice(t, 1, 'KHR_techniques_webgl');
	//gltf.extensionsUsed.splice(v, 1, 'KHR_techniques_webgl');

	QJsonArray jsonArray;
	jsonArray.push_back(QJsonValue("KHR_techniques_webgl"));

	m_rootObj["extensionsUsed"] = jsonArray;
	m_rootObj["extensionsRequired"] = jsonArray;
#pragma endregion

#pragma region step2
	//<step2>
	//gltf.extensions = gltf.extensions || {};
	//gltf.extensions = gltf.extensions || {};
	//gltf.extensions['KHR_techniques_webgl'] = {};
	//gltf.extensions['KHR_techniques_webgl'].programs = gltf.programs;
	//gltf.extensions['KHR_techniques_webgl'].shaders = gltf.shaders;
	//gltf.extensions['KHR_techniques_webgl'].techniques = gltf.techniques;

	QJsonObject json_KHR_techniques_webgl;
	json_KHR_techniques_webgl.insert("programs", m_rootObj["programs"].toArray());
	json_KHR_techniques_webgl.insert("shaders", m_rootObj["shaders"].toArray());
	json_KHR_techniques_webgl.insert("techniques", m_rootObj["techniques"].toArray());

	QJsonObject json_extensions;
	json_extensions.insert("KHR_techniques_webgl", json_KHR_techniques_webgl);   //创建一个 KHR_techniques_webgl
	m_rootObj.insert("extensions", json_extensions);

#pragma endregion

#pragma region step3
	//<step3>  没有赋值成功 ???  已经解决：QjsonValueRef to...()  返回的是一个副本， 而不是类似引用或者的指针
	//gltf.materials[index].extensions['KHR_technique_webgl'].values = gltf.materials[index].values;

	QJsonArray jsArr_materials;
	QJsonObject jsObj_materials;
	QJsonObject jsObj_mat_ext;
	QJsonObject jsObj_mat_ext_KHR;

	jsArr_materials = m_rootObj["materials"].toArray();
	jsObj_materials = jsArr_materials[0].toObject();
	jsObj_mat_ext = jsObj_materials["extensions"].toObject();
	jsObj_mat_ext_KHR = jsObj_mat_ext["KHR_technique_webgl"].toObject();

	jsObj_mat_ext_KHR["values"] = ((jsArr_materials[0]).toObject())["values"].toObject();
	jsObj_mat_ext["KHR_technique_webgl"] = jsObj_mat_ext_KHR;
	jsObj_materials["extensions"] = jsObj_mat_ext;
	jsArr_materials[0] = jsObj_materials;
	m_rootObj["materials"] = jsArr_materials;

	//gltf.materials[index].extensions['KHR_techniques_webgl'] = gltf.materials[index].extensions['KHR_technique_webgl'];
	QJsonArray jsArr_materials2;
	QJsonObject jsObj_materials2;
	QJsonObject jsObj_mat_ext2;

	QJsonObject jsonObject2 =
		((((m_rootObj["materials"]).toArray())[0].toObject())["extensions"].toObject())["KHR_technique_webgl"].toObject();   //Create   "KHR_techniques_webgl"-value

	jsArr_materials2 = m_rootObj["materials"].toArray();
	jsObj_materials2 = jsArr_materials2[0].toObject();
	jsObj_mat_ext2 = jsObj_materials2["extensions"].toObject();
	jsObj_mat_ext2.insert("KHR_techniques_webgl", jsonObject2);

	jsObj_materials2["extensions"] = jsObj_mat_ext2;
	jsArr_materials2[0] = jsObj_materials2;
	m_rootObj["materials"] = jsArr_materials2;

#pragma endregion


#pragma region step3.1
	//<step3.1>
	//for (var value in vtxfMaterialExtension.values) {
	//	var us = techniques[vtxfMaterialExtension.technique].uniforms;
	//	for (var key in us) {
	//		if (us[key] == = value) {
	//			vtxfMaterialExtension.values[key] = vtxfMaterialExtension.values[value];
	//			delete vtxfMaterialExtension.values[value];
	//			break;
	//		}
	//	}
	//};

	QJsonArray jsArr_materials3_1;
	QJsonObject jsObj_materials3_1;
	QJsonObject jsObj_mat_ext3_1;
	QJsonObject jsObj_mat_ext_KHRs3_1;
	QJsonObject jsObj_mat_ext_KHRs_val3_1;

	jsArr_materials3_1 = m_rootObj["materials"].toArray();
	jsObj_materials3_1 = jsArr_materials3_1[0].toObject();
	jsObj_mat_ext3_1 = jsObj_materials3_1["extensions"].toObject();
	jsObj_mat_ext_KHRs3_1 = jsObj_mat_ext3_1["KHR_techniques_webgl"].toObject();
	jsObj_mat_ext_KHRs_val3_1 = jsObj_mat_ext_KHRs3_1["values"].toObject();

	QJsonObject jsObj_ext_KHRs_tec =
		(((m_rootObj["extensions"].toObject())["KHR_techniques_webgl"].toObject())["techniques"].toArray())[0].toObject();

	for (int i = 0; i < jsObj_mat_ext_KHRs_val3_1.keys().size(); i++)
	{
		QJsonObject json_ext_HKRs_tec_uni = jsObj_ext_KHRs_tec["uniforms"].toObject();
		for (int j = 0; j < json_ext_HKRs_tec_uni.keys().size(); j++)
		{
			QString key_val = jsObj_mat_ext_KHRs_val3_1.keys().at(i);
			QString key_uni = json_ext_HKRs_tec_uni.keys().at(j);

			if ((json_ext_HKRs_tec_uni)[key_uni].toString() == key_val)
			{
				QJsonObject jsObj_temp_3_1 = jsObj_mat_ext_KHRs_val3_1[key_val].toObject();

				jsObj_mat_ext_KHRs_val3_1.insert(key_uni, jsObj_temp_3_1);  //先增加，后删除（不可先删除，后增加，删掉之后的值就会不见了）
				jsObj_mat_ext_KHRs_val3_1.remove(key_val);

				jsObj_mat_ext_KHRs3_1.insert("values", jsObj_mat_ext_KHRs_val3_1);
				jsObj_mat_ext3_1.insert("KHR_techniques_webgl", jsObj_mat_ext_KHRs3_1);  //没有这一步,下面的就会出错 QJsonObject （的值是多个Object，而非只有一个）
				jsObj_materials3_1.insert("extensions", jsObj_mat_ext3_1);

			}
		}
	}

	jsArr_materials3_1[0] = jsObj_materials3_1;
	m_rootObj["materials"] = jsArr_materials3_1;

#pragma endregion



#pragma region step4
	//<step4>
	//techniques.forEach(function(t) {
	//	for (var attribute in t.attributes) {
	//		var name = t.attributes[attribute];
	//		t.attributes[attribute] = t.parameters[name];
	//	};

	QJsonObject jsObj_extensions4;
	QJsonObject jsObj_ext_KHRs4;

	QJsonArray  jsonArray_ext_KHRs_tec4;
	QJsonObject jsObj_ext_KHRs_tec4;
	QJsonObject jsObj_ext_KHRs_tec_att4;
	QJsonObject jsObj_ext_KHRs_tec_uni4;

	jsObj_extensions4 = m_rootObj["extensions"].toObject();                   //= 左值 准备工作
	jsObj_ext_KHRs4 = jsObj_extensions4["KHR_techniques_webgl"].toObject();
	jsonArray_ext_KHRs_tec4 = jsObj_ext_KHRs4["techniques"].toArray();
	jsObj_ext_KHRs_tec4 = jsonArray_ext_KHRs_tec4[0].toObject();

	QJsonObject jsObj_ext_KHRs_tec_par_temp4 =              //= 右值 准备工作
		((((m_rootObj["extensions"].toObject())["KHR_techniques_webgl"].toObject())["techniques"].toArray())[0].toObject())["parameters"].toObject();

	//------------------------------------------------------------------------------
	//修改extensions-KHR_techniques_webgl-techniques-attributes = parameters (右边赋值左边)
	jsObj_ext_KHRs_tec_att4 = jsObj_ext_KHRs_tec4["attributes"].toObject();

	for (int i = 0; i < jsObj_ext_KHRs_tec_att4.keys().size(); i++)
	{
		for (int j = 0; j < jsObj_ext_KHRs_tec_par_temp4.keys().size(); j++)
		{
			QString key_att = jsObj_ext_KHRs_tec_att4.keys().at(i);
			QString key_par = jsObj_ext_KHRs_tec_par_temp4.keys().at(j);

			if (jsObj_ext_KHRs_tec_att4[key_att].toString() == key_par)
			{
				QString str_temp = jsObj_ext_KHRs_tec_att4[key_att].toString();
				QJsonObject jsObj_ext_KHRs_tec_att_ = jsObj_ext_KHRs_tec_par_temp4[str_temp].toObject();
				jsObj_ext_KHRs_tec_att4.insert(key_att, jsObj_ext_KHRs_tec_att_);
			}
		}
	}

	//------------------------------------------------------------------------------
	//修改extensions-KHR_techniques_webgl-techniques-uniforms = parameters    (右边赋值左边)

	jsObj_ext_KHRs_tec_uni4 = jsObj_ext_KHRs_tec4["uniforms"].toObject();

	for (int i = 0; i < jsObj_ext_KHRs_tec_uni4.keys().size(); i++)
	{
		for (int j = 0; j < jsObj_ext_KHRs_tec_par_temp4.keys().size(); j++)
		{
			QString key_uni = jsObj_ext_KHRs_tec_uni4.keys().at(i);
			QString key_par = jsObj_ext_KHRs_tec_par_temp4.keys().at(j);

			if (jsObj_ext_KHRs_tec_uni4[key_uni].toString() == key_par)
			{
				QString str_temp = jsObj_ext_KHRs_tec_uni4[key_uni].toString();
				QJsonObject jsObj_ext_KHRs_tec_uni_ = jsObj_ext_KHRs_tec_par_temp4[str_temp].toObject();
				jsObj_ext_KHRs_tec_uni4.insert(key_uni, jsObj_ext_KHRs_tec_uni_);
			}
		}
	}

	jsObj_ext_KHRs_tec4["attributes"] = jsObj_ext_KHRs_tec_att4;
	jsObj_ext_KHRs_tec4["uniforms"] = jsObj_ext_KHRs_tec_uni4;
	jsonArray_ext_KHRs_tec4[0] = jsObj_ext_KHRs_tec4;
	jsObj_ext_KHRs4["techniques"] = jsonArray_ext_KHRs_tec4;
	jsObj_extensions4["KHR_techniques_webgl"] = jsObj_ext_KHRs4;
	m_rootObj["extensions"] = jsObj_extensions4;

#pragma endregion
#pragma endregion

//
//#pragma region 暴力修改版_已弃_易理解
//#pragma region step1
//	//<step1>
//	//1gltf.extensionsRequired.splice(t, 1, 'KHR_techniques_webgl');
//	//gltf.extensionsUsed.splice(v, 1, 'KHR_techniques_webgl');
//
//	QJsonArray jsonArray;
//	jsonArray.push_back(QJsonValue("KHR_techniques_webgl"));
//
//	m_rootObj["extensionsUsed"] = jsonArray;
//	m_rootObj["extensionsRequired"] = jsonArray;
//#pragma endregion
//
//#pragma region step2
//	//<step2>
//	//gltf.extensions = gltf.extensions || {};
//	//gltf.extensions = gltf.extensions || {};
//	//gltf.extensions['KHR_techniques_webgl'] = {};
//	//gltf.extensions['KHR_techniques_webgl'].programs = gltf.programs;
//	//gltf.extensions['KHR_techniques_webgl'].shaders = gltf.shaders;
//	//gltf.extensions['KHR_techniques_webgl'].techniques = gltf.techniques;
//
//	QJsonObject js_KHR_techniques_webgl;
//	js_KHR_techniques_webgl.insert("programs", m_rootObj["programs"].toArray());
//	js_KHR_techniques_webgl.insert("shaders", m_rootObj["shaders"].toArray());
//	js_KHR_techniques_webgl.insert("techniques", m_rootObj["techniques"].toArray());
//
//	QJsonObject js_extensions;
//	js_extensions.insert("KHR_techniques_webgl", js_KHR_techniques_webgl);   //创建一个 KHR_techniques_webgl
//	m_rootObj.insert("extensions", js_extensions);
//
//#pragma endregion
//
//
//#pragma region step3
//	//<step3>  没有赋值成功 ???  已经解决：QjsonValueRef to...()  返回的是一个副本， 而不是类似引用或者的指针
//	//gltf.materials[index].extensions['KHR_technique_webgl'].values = gltf.materials[index].values;
//
//	QJsonArray jsArr_materials;
//	QJsonObject jsObj_materials;
//	QJsonObject jsObj_mat_ext;
//	QJsonObject jsObj_mat_ext_KHR;
//
//	jsArr_materials = m_rootObj["materials"].toArray();
//	jsObj_materials = jsArr_materials[0].toObject();
//	jsObj_mat_ext = jsObj_materials["extensions"].toObject();
//	jsObj_mat_ext_KHR = jsObj_mat_ext["KHR_technique_webgl"].toObject();
//
//	jsObj_mat_ext_KHR["values"] = (jsArr_materials[0].toObject())["values"].toObject();
//
//	jsObj_mat_ext["KHR_technique_webgl"] = jsObj_mat_ext_KHR;
//	jsObj_materials["extensions"] = jsObj_mat_ext;
//	jsArr_materials[0] = jsObj_materials;
//	m_rootObj["materials"] = jsArr_materials;
//
//	//gltf.materials[index].extensions['KHR_techniques_webgl'] = gltf.materials[index].extensions['KHR_technique_webgl'];
//	QJsonArray jsArr_materials2;
//	QJsonObject jsObj_materials2;
//	QJsonObject jsObj_mat_ext2;
//
//	QJsonObject jsonObject2 = (((m_rootObj["materials"].toArray())[0].toObject())["extensions"].toObject())["KHR_technique_webgl"].toObject();   //Create   "KHR_techniques_webgl"-value
//
//	jsArr_materials2 = m_rootObj["materials"].toArray();
//	jsObj_materials2 = jsArr_materials2[0].toObject();
//	jsObj_mat_ext2 = jsObj_materials2["extensions"].toObject();
//
//	jsObj_mat_ext2.insert("KHR_techniques_webgl", jsonObject2);
//
//	jsObj_materials2["extensions"] = jsObj_mat_ext2;
//	jsArr_materials2[0] = jsObj_materials2;
//	m_rootObj["materials"] = jsArr_materials2;
//#pragma endregion
//
//
//#pragma region step3.1
//	//<step3.1>
//	//for (var value in vtxfMaterialExtension.values) {
//	//	var us = techniques[vtxfMaterialExtension.technique].uniforms;
//	//	for (var key in us) {
//	//		if (us[key] == = value) {
//	//			vtxfMaterialExtension.values[key] = vtxfMaterialExtension.values[value];
//	//			delete vtxfMaterialExtension.values[value];
//	//			break;
//	//		}
//	//	}
//	//};
//
//	QJsonArray jsArr_materials3_1;
//	QJsonObject jsObj_materials3_1;
//	QJsonObject jsObj_mat_ext3_1;
//	QJsonObject jsObj_mat_ext_KHRs3_1;
//	QJsonObject jsObj_mat_ext_KHRs_val3_1;
//
//	jsArr_materials3_1 = m_rootObj["materials"].toArray();
//	jsObj_materials3_1 = jsArr_materials3_1[0].toObject();
//	jsObj_mat_ext3_1 = jsObj_materials3_1["extensions"].toObject();
//	jsObj_mat_ext_KHRs3_1 = jsObj_mat_ext3_1["KHR_techniques_webgl"].toObject();
//	jsObj_mat_ext_KHRs_val3_1 = jsObj_mat_ext_KHRs3_1["values"].toObject();
//
//	QJsonObject jsObj_temp_3_1 = jsObj_mat_ext_KHRs_val3_1["diffuse"].toObject();
//
//	jsObj_mat_ext_KHRs_val3_1.insert("u_diffuse", jsObj_temp_3_1);  //先增加，后删除（不可先删除，后增加，删掉之后的值就会不见了）
//	jsObj_mat_ext_KHRs_val3_1.remove("diffuse");
//
//	jsObj_mat_ext_KHRs3_1.insert("values", jsObj_mat_ext_KHRs_val3_1);
//	jsObj_mat_ext3_1.insert("KHR_techniques_webgl", jsObj_mat_ext_KHRs3_1);  //没有这一步,下面的就会出错 QJsonObject （的值是多个Object，而非只有一个）
//	jsObj_materials3_1.insert("extensions", jsObj_mat_ext3_1);
//	jsArr_materials3_1[0] = jsObj_materials3_1;
//	m_rootObj["materials"] = jsArr_materials3_1;
//
//#pragma endregion
//
//
//
//#pragma region step4
//	//<step4>
//	//techniques.forEach(function(t) {
//	//	for (var attribute in t.attributes) {
//	//		var name = t.attributes[attribute];
//	//		t.attributes[attribute] = t.parameters[name];
//	//	};
//
//	QJsonObject jsObj_extensions4;
//	QJsonObject jsObj_ext_KHRs4;
//
//	QJsonArray  jsonArray_ext_KHRs_tec4;
//	QJsonObject jsObj_ext_KHRs_tec4;
//	QJsonObject jsObj_ext_KHRs_tec_att4;
//	QJsonObject jsObj_ext_KHRs_tec_uni4;
//
//	QJsonObject jsObj_ext_KHRs_tec_att4_abt;
//	QJsonObject jsObj_ext_KHRs_tec_att4_apo;
//	QJsonObject jsObj_ext_KHRs_tec_att4_ate;
//
//	QJsonObject jsObj_ext_KHRs_tec_uni4_udi;
//	QJsonObject jsObj_ext_KHRs_tec_uni4_umo;
//	QJsonObject jsObj_ext_KHRs_tec_uni4_upr;
//
//	jsObj_extensions4 = m_rootObj["extensions"].toObject();                   //= 左值 准备工作
//	jsObj_ext_KHRs4 = jsObj_extensions4["KHR_techniques_webgl"].toObject();
//	jsonArray_ext_KHRs_tec4 = jsObj_ext_KHRs4["techniques"].toArray();
//	jsObj_ext_KHRs_tec4 = jsonArray_ext_KHRs_tec4[0].toObject();
//
//
//	QJsonObject jsObj_ext_KHRs_tec_par_temp4 =       //= 右值 准备工作
//		((((m_rootObj["extensions"].toObject())["KHR_techniques_webgl"].toObject())["techniques"].toArray())[0].toObject())["parameters"].toObject();
//
//	//------------------------------------------------------------------------------
//	//修改extensions-KHR_techniques_webgl-techniques-attributes = parameters (右边赋值左边)
//	jsObj_ext_KHRs_tec_att4 = jsObj_ext_KHRs_tec4.find("attributes").value().toObject();
//
//	jsObj_ext_KHRs_tec_att4_abt = jsObj_ext_KHRs_tec_par_temp4["batchid"].toObject();
//	jsObj_ext_KHRs_tec_att4_apo = jsObj_ext_KHRs_tec_par_temp4["position"].toObject();
//	jsObj_ext_KHRs_tec_att4_ate = jsObj_ext_KHRs_tec_par_temp4["texcoord0"].toObject();
//
//	jsObj_ext_KHRs_tec_att4.insert("a_batchid", jsObj_ext_KHRs_tec_att4_abt);     //插入到上面 删除得到地方  <==>  Object替换Qstring
//	jsObj_ext_KHRs_tec_att4.insert("a_position", jsObj_ext_KHRs_tec_att4_apo);
//	jsObj_ext_KHRs_tec_att4.insert("a_texcoord0", jsObj_ext_KHRs_tec_att4_ate);
//
//	//------------------------------------------------------------------------------
//	//修改extensions-KHR_techniques_webgl-techniques-uniforms = parameters    (右边赋值左边)
//
//	jsObj_ext_KHRs_tec_uni4 = jsObj_ext_KHRs_tec4["uniforms"].toObject();
//
//	jsObj_ext_KHRs_tec_uni4_udi = jsObj_ext_KHRs_tec_par_temp4["diffuse"].toObject();      //= 右值 准备工作
//	jsObj_ext_KHRs_tec_uni4_umo = jsObj_ext_KHRs_tec_par_temp4["modelViewMatrix"].toObject();
//	jsObj_ext_KHRs_tec_uni4_upr = jsObj_ext_KHRs_tec_par_temp4["projectionMatrix"].toObject();
//
//	jsObj_ext_KHRs_tec_uni4.insert("u_diffuse", jsObj_ext_KHRs_tec_uni4_udi);     //插入到上面 删除得到地方  <==>  Object替换Qstring
//	jsObj_ext_KHRs_tec_uni4.insert("u_modelViewMatrix", jsObj_ext_KHRs_tec_uni4_umo);
//	jsObj_ext_KHRs_tec_uni4.insert("u_projectionMatrix", jsObj_ext_KHRs_tec_uni4_upr);
//
//	//this END
//	//------------------------------------------------------------------------------
//
//	jsObj_ext_KHRs_tec4["attributes"] = jsObj_ext_KHRs_tec_att4;
//	jsObj_ext_KHRs_tec4["uniforms"] = jsObj_ext_KHRs_tec_uni4;
//	jsonArray_ext_KHRs_tec4[0] = jsObj_ext_KHRs_tec4;
//	jsObj_ext_KHRs4["techniques"] = jsonArray_ext_KHRs_tec4;
//	jsObj_extensions4["KHR_techniques_webgl"] = jsObj_ext_KHRs4;
//	m_rootObj["extensions"] = jsObj_extensions4;
//
//	//myJsonDisplay();
//	//printf("baocun-----------------------------------\n");
//	//ofstream fFile3;
//
//	//fFile3.open("D:/programming/DataDas/3dtiles/json/json_outBaocun.json", ios::binary /*| ios::app*/ | ios::in | ios::out);
//	//string strModify3 = QString(QJsonDocument(m_rootObj).toJson()).toStdString();
//
//	//fFile3 << strModify3 << endl;
//	//fFile3.close();
//
//	//printf("222-----------------------------------\n");
//#pragma endregion
//#pragma endregion
//

	return true;
}

void MY_QT_JSON::myJsonOutStr(string& str)  //将修改好的JSON格式，替换输出参数str
{
	if (str.empty())
		return;

	QJsonObject jsonObject = m_rootObj;
	QString qstr = QString(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact));
	str = qstr.toStdString();
}
