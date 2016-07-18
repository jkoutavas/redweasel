#ifndef APPPROPERTIES_H_INCLUDED
#define APPPROPERTIES_H_INCLUDED

#include "PropsFile.h"

class AppProperties
{
public:
	juce_DeclareSingleton(AppProperties, true);
    AppProperties();
    ~AppProperties();

public:
    String getValue(StringRef keyName, const String& defaultReturnValue = String());
    int getIntValue(StringRef keyName, int defaultReturnValue = 0);
    bool getBoolValue(StringRef keyName, bool defaultReturnValue = false);
    XmlElement* getXmlValue(StringRef keyName);
    void setValue(const String& keyName, const var& value);
    void setValue(const String& keyName, const XmlElement* xml);
    void removeValue(StringRef keyName);
    bool containsKey(StringRef keyName);
    void clear();

private:
    ScopedPointer <PropsFile> userProps;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppProperties);
};

#endif  // APPPROPERTIES_H_INCLUDED
