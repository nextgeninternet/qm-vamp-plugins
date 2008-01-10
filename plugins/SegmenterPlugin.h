/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
 * SegmenterPlugin.h
 *
 * Created by Mark Levy on 24/03/2006.
 * Copyright 2006 Centre for Digital Music, Queen Mary, University of London.
 * All rights reserved.
 */

#ifndef _SEGMENTER_PLUGIN_H_
#define _SEGMENTER_PLUGIN_H_

#include <vamp-sdk/Plugin.h>
#include <vamp-sdk/RealTime.h>
#include "dsp/segmentation/Segmenter.h"
#include "dsp/segmentation/segment.h"

class Decimator;

class SegmenterPlugin : public Vamp::Plugin
{
public:
    SegmenterPlugin(float inputSampleRate);
    virtual ~SegmenterPlugin();
	
    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();
	
    std::string getIdentifier() const { return "qm-segmenter"; }
    std::string getName() const { return "Segmenter"; }
    std::string getDescription() const { return "Divide the track into a sequence of consistent segments"; }
    std::string getMaker() const;
    int getPluginVersion() const;
    std::string getCopyright() const;
	
    size_t getPreferredStepSize() const;
    size_t getPreferredBlockSize() const;
    InputDomain getInputDomain() const { return TimeDomain; }
    
    SegmenterPlugin::ParameterList getParameterDescriptors() const;
    float getParameter(std::string param) const;
    void setParameter(std::string param, float value);
    
    OutputList getOutputDescriptors() const;
    
    FeatureSet process(const float *const *inputBuffers, Vamp::RealTime timestamp);
    
    FeatureSet getRemainingFeatures();
	
protected:
    mutable Segmenter* segmenter;
    mutable int hopsize;
    mutable int windowsize;
    int nSegmentTypes;
    feature_types featureType;	// 1 = constant-Q, 2 = chroma
    
    void makeSegmenter() const;
};

#endif

