#pragma once

#ifndef AUM_WORKSTATION_MATH_H
#include <Math/AUM-Workstation-Math.h>
#define AUM_WORKSTATION_MATH_H
#endif // !AUM_WORKSTATION_MATH_H

#define AUM_API_SAMPLE_RATE_44100 44100
#define AUM_API_SAMPLE_RATE_88200 88200

namespace AUM_API_Synthesis {

    class AUMOscillator
    {
    /// <summary>
    /// USE VOID TO CAST TO FLOAT
    /// </summary>
    public:
        float GetSinPoint(float i, float frequency, float sampleRate);
    };

}