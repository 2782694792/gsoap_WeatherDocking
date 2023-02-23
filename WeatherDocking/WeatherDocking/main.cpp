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
		= (char *)("http://ws.webxml.com.cn/WebServices/WeatherWS.asmx"); // �����ַ
    
	WeatherWSSoapProxy soap(SOAP_C_UTFSTRING); // soap�ӿ�
    
    _ns1__getWeather city_name; // �����������
    city_name.theCityCode = new string( "" ); // Ĭ���Ϻ�
    city_name.theUserID = new string( "" );

    _ns1__getWeatherResponse weather_res; // �������
    
    int xlt = soap.getWeather( web_url, NULL, &city_name, weather_res ); // ���ýӿ� getWeather
    
    ns1__ArrayOfString * aos;
    if ( xlt == SOAP_OK ) // �жϽӿڷ���ֵ, SOAP_OK ��ʾ�ɹ�
    {
        cout << "retcode: " << xlt << endl;
       
		aos = weather_res.getWeatherResult; // ��ȡ���ؽ��
        
        vector<string> result = aos->string; //result.swap(aos.string);
        for ( auto it = result.begin(); it != result.end(); it++ ) // ��ӡ���ؽ��
        {
            cout << *it << endl;
        }
    }
	else
	{
		soap.soap_stream_fault(std::cerr); // getWeather ʧ��ԭ��
	}
	
	getchar();

	soap.destroy();
    return 0;

}