#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "soapWeatherWSSoapProxy.h"
#include "WeatherWSSoap.nsmap"

using namespace std;

int main( int argc, char ** argv )
{
    system( "chcp 65001" );
    
    char * web_url 
		= (char *)("http://ws.webxml.com.cn/WebServices/WeatherWS.asmx"); // 请求地址
    
	WeatherWSSoapProxy soap(SOAP_C_UTFSTRING); // soap接口
    
    _ns1__getWeather city_name; // 构造输入参数
    city_name.theCityCode = new string( "" ); // 默认上海
    city_name.theUserID = new string( "" );

    _ns1__getWeatherResponse weather_res; // 输出参数
    
    int xlt = soap.getWeather( web_url, NULL, &city_name, weather_res ); // 调用接口 getWeather
    
    ns1__ArrayOfString * aos;
    if ( xlt == SOAP_OK ) // 判断接口返回值, SOAP_OK 表示成功
    {
        cout << "retcode: " << xlt << endl;
       
		aos = weather_res.getWeatherResult; // 获取返回结果
        
        vector<string> result = aos->string; //result.swap(aos.string);
        for ( auto it = result.begin(); it != result.end(); it++ ) // 打印返回结果
        {
            cout << *it << endl;
        }
    }
	else
	{
		soap.soap_stream_fault(std::cerr); // getWeather 失败原因
	}
	
	getchar();

	soap.destroy();
    return 0;

}