#include "AppProperties.h"

juce_ImplementSingleton(AppProperties);

AppProperties::AppProperties()
{
    PropertiesFile::Options options;
    options.applicationName     = ProjectInfo::projectName;
    options.filenameSuffix      = "settings";
    options.osxLibrarySubFolder = "Preferences";
    options.commonToAllUsers    = false;
    options.storageFormat       = PropertiesFile::storeAsBinary;
    userProps = new PropsFile(options);
}

AppProperties::~AppProperties()
{
    clearSingletonInstance();
}

#if 0
#pragma mark - property bridging
#endif

String
AppProperties::getValue(StringRef keyName, const String& defaultReturnValue)
{
    return userProps->getValue(keyName, defaultReturnValue);
}

int
AppProperties::getIntValue(StringRef keyName, int defaultReturnValue)
{
    return userProps->getIntValue(keyName, defaultReturnValue);
}

bool
AppProperties::getBoolValue(StringRef keyName, bool defaultReturnValue)
{
    return userProps->getBoolValue(keyName, defaultReturnValue);
}

XmlElement*
AppProperties::getXmlValue(StringRef keyName)
{
    return userProps->getXmlValue(keyName);
}

void
AppProperties::setValue(const String& keyName, const var& value)
{
    userProps->setValue(keyName, value);
}

void
AppProperties::setValue(const String& keyName, const XmlElement* xml)
{
    userProps->setValue(keyName, xml);
}

void
AppProperties::removeValue(StringRef keyName)
{
    userProps->removeValue(keyName);
}

bool
AppProperties::containsKey(StringRef keyName)
{
    return userProps->containsKey(keyName);
}

void
AppProperties::clear()
{
    userProps->clear();
}
