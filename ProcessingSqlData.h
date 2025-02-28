#ifndef _PROCESSINGSQLDATA_H_
#define _PROCESSINGSQLDATA_H_

#include <map>
#include <string>
#include <vector>
#include "CalcDateSingleton.h"

class ProcessingSqlData
{
public:
	ProcessingSqlData(
		std::map<std::string, float>* mapThisYearG,
		std::map<std::string, float>* mapLastYearG,
		std::map<std::string, float>* mapDiffG,
		std::map<std::string, float>* mapBuyG,
		std::vector<std::string>* vecAllG,
		CalcDateSingleton* myDate
	);
	~ProcessingSqlData();
private:
		std::map<std::string, float>* mapThisYearG;
		std::map<std::string, float>* mapLastYearG;
		std::map<std::string, float>* mapDiffG;
		std::map<std::string, float>* mapBuyG;
		CalcDateSingleton* myDate;
		std::vector<std::string>* vecAllG;
		std::vector<std::string>* vecAllGt;

		void getVecAllGAndGt( );


		void downloadFromSql(
			std::vector<std::vector<std::string>>* thisYearZaiko,
			std::vector<std::vector<std::string>>* lastYearZaiko,
			std::vector<std::vector<std::string>>* buyMaterials
		);

		void changeToKg(
			std::vector<std::vector<std::string>>* thisYearZaiko,
			std::vector<std::vector<std::string>>* lastYearZaiko,
			std::vector<std::vector<std::string>>* buyMaterials
		);

		void separate(
			std::vector<std::vector<std::string>>* thisYearZaiko,
			std::vector<std::vector<std::string>>* thisYearG,
			std::vector<std::vector<std::string>>* thisYearGt,
			std::vector<std::vector<std::string>>* lastYearZaiko,
			std::vector<std::vector<std::string>>* lastYearG,
			std::vector<std::vector<std::string>>* lastYearGt
		);

		void vecToMap(
			//2次元ベクターのkeyColとvalColでmapを作る
			std::vector<std::vector<std::string>>* vec,
			int kyeCol,
			int valCol,
			std::map<std::string, float>* map
		);
		
		void gtMinusGt(
			std::map<std::string, float>* mapThisYearGt,
			std::map<std::string, float>* mapLastYearGt,
		    std::map<std::string, float>* mapDiffGt
		);

		void gtToG(
			std::map<std::string, float>* mapDiffGt,
			std::map<std::string, float>* mapDiffG
		);

};
#endif _PROCESSINGSQLDATA_H_

