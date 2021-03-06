#include "HelperFunc.h"
//#include "cocos2d.h"
extern "C" {
#include "lua.h"
#include "xxtea.h"
}
#include "CCLuaEngine.h"

USING_NS_CC;
unsigned char* CZHelperFunc::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
  unsigned long size;
  unsigned char* buf = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, &size);
  if (NULL==buf) return NULL;
 
  CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
  unsigned char* buffer = NULL;
 
    bool isXXTEA = stack && stack->m_xxteaEnabled;
    for (unsigned int i = 0; isXXTEA && i < stack->m_xxteaSignLen && i < size; ++i)
    {
        isXXTEA = buf[i] == stack->m_xxteaSign[i];
    }
 
    if (isXXTEA)
    {
        // decrypt XXTEA
        xxtea_long len = 0;
        buffer = xxtea_decrypt(buf + stack->m_xxteaSignLen,
                               (xxtea_long)size - (xxtea_long)stack->m_xxteaSignLen,
                               (unsigned char*)stack->m_xxteaKey,
                               (xxtea_long)stack->m_xxteaKeyLen,
                               &len);
        delete []buf;
        buf = NULL;
        size = len;
    }
    else
    {
        buffer = buf;
    }
 
    if (pSize) *pSize = size;
    return buffer;
}
