#ifndef JUCE_PROPSFILE_H_INCLUDED
#define JUCE_PROPSFILE_H_INCLUDED

#include "JuceHeader.h"

class PropsFile  : public PropertySet,
                   public ChangeBroadcaster,
                   private Timer
{
public:
    explicit PropsFile (const PropertiesFile::Options& options);
    ~PropsFile();
    
    const File& getFile() const { return file; }
    bool reload();
    bool saveIfNeeded();
    bool save();

protected:
    void propertyChanged() override;

private:
    File file;
    PropertiesFile::Options options;
    bool loadedOk, needsWriting;

    typedef const ScopedPointer<InterProcessLock::ScopedLockType> ProcessScopedLock;
    InterProcessLock::ScopedLockType* createProcessLock() const;

    void timerCallback() override;
    bool saveAsXml();
    bool saveAsBinary();
    bool loadAsXml();
    bool loadAsBinary();
    bool loadAsBinary (InputStream&);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropsFile)
};

#endif   // JUCE_PROPSFILE_H_INCLUDED
