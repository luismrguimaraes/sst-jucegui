//
// Created by Paul Walker on 5/24/22.
//

#ifndef SST_JUCEGUI_NAMEDPANEL_H
#define SST_JUCEGUI_NAMEDPANEL_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <string>

namespace sst::jucegui::components
{
struct NamedPanel : public juce::Component
{
    NamedPanel(const std::string &name);
    ~NamedPanel();

    void paint(juce::Graphics &g) override;
    void resized() override;

    void setContentAreaComponent(std::unique_ptr<juce::Component> &&c)
    {
        contentAreaComp = std::move(c);
        addAndMakeVisible(*contentAreaComp);
        resized();
    }
    void setHeaderControlAreaComponent(std::unique_ptr<juce::Component> &&c)
    {
        headerControlAreaComp = std::move(c);
        addAndMakeVisible(*headerControlAreaComp);
        resized();
    }

  protected:
    std::string name;
    std::unique_ptr<juce::Component> contentAreaComp, headerControlAreaComp;
};
} // namespace sst::jucegui::components

#endif // SST_JUCEGUI_NAMEDPANEL_H
