/*
 * sst-jucegui - a set of widgets for ShortCircuit, SurgeXT2, and others
 * Copyright 2022 to authors per the github transaction log
 *
 * Released under the MIT license. See 'LICENSE.md' for details.
 */

/**
 * Provide a collection of layout helpers for dealing with juce::Rectangles and associated
 * resized methods.
 */

#ifndef SST_JUCEGUI_LAYOUTS_H
#define SST_JUCEGUI_LAYOUTS_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

namespace sst::jucegui::style
{
/**
 * EvenDivision<T> provides a mechanism to evenly divide a juce::Rectangle<T>
 * into a collection of uniform sub-boxes along an axis. You can use this class
 * in an interator context. For instance
 *
 * ```
 * auto q = EvenDivision<float>(r, 10, EvenDivision<float>::Horizontal);
 * for (const auto &subRect : q )
 * {
 * }
 * ```
 *
 * @tparam T the storage type in the juce::Rectangle
 */
template <typename T> struct EvenDivision
{
    enum Orientation
    {
        HORIZONTAL,
        VERTICAL
    };

    /**
     * Construct an even division of a rectangle. Supports an iterator semantic so
     * once constructed you can use `for (const auto &r : evendiv)` type loops.
     *
     * @param divide The item to divide into even sections
     * @param into The number of sections to divide into
     * @param thisway The orientation (horizontal or vertical) for the splits.
     */
    EvenDivision(const juce::Rectangle<T> &divide, int into, const Orientation &thisway)
    {
        jassert(into > 0);
        if (thisway == HORIZONTAL)
        {
            auto w = divide.getWidth() / into;
            auto q = divide.withWidth(w);
            for (int i = 0; i < into; ++i)
            {
                store.push_back(q);
                q = q.translated(w, 0);
            }
        }
        else
        {
            auto h = divide.getHeight() / into;
            auto q = divide.withHeight(h);
            for (int i = 0; i < into; ++i)
            {
                store.push_back(q);
                q = q.translated(0, h);
            }
        }
    }

    typedef std::vector<juce::Rectangle<T>> store_t;
    store_t store;
    typedef typename store_t::iterator iterator;
    typedef const typename store_t::const_iterator const_iterator;

    iterator begin() { return store.begin(); }
    const_iterator begin() const { return store.begin(); }
    iterator end() { return store.end(); }
    const_iterator end() const { return store.end(); }
};
} // namespace sst::jucegui::style

#endif // SST_JUCEGUI_LAYOUTS_H