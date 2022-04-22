#include "AUM-Oscillator.h"

namespace AUM_API_Synthesis {

    float AUMOscillator::GetSinPoint
    
        (float i, float frequency, float sampleRate) {
        return (float)(sin(2 * M_PI * frequency * i) / sampleRate);
    }

}