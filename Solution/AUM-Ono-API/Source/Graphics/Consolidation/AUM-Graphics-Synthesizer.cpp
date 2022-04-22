#include "AUM-Graphics-Synthesizer.h"

namespace AUM_API_Synthesis {

    IAUMGraphicsSynthesizer::IAUMGraphicsSynthesizer

        (string name) {
        this->Name = name;
        this->oscillator = AUMOscillator();
    }

    void IAUMGraphicsSynthesizer::UseFFOZZSamplerateAndBufferTheWave

    (float frequency, int resolution) {

        const int sampleRate = AUM_API_SAMPLE_RATE_44100;

        float amplitude = sampleRate / 4;

        int index;
        for (float i = 0; i < sampleRate; i++)
        {
            int index = (int)i;
            _Graphics.RawDataCacheFFOZZ[index].x = -.5 + (i / sampleRate) * resolution;
            _Graphics.RawDataCacheFFOZZ[index].y = amplitude * this->oscillator.GetSinPoint(
                _Graphics.RawDataCacheFFOZZ[index].x, frequency, sampleRate
            );
        }
        _Graphics.VertexBuffer = AUMOnoAPIGraphicsVertexBuffer(
            sizeof _Graphics.RawDataCacheFFOZZ, _Graphics.RawDataCacheFFOZZ
        );
        _Graphics.VertexBuffer.Bind();
    }

    void IAUMGraphicsSynthesizer::UseEETZZSamplerateAndBufferTheWave

    (float frequency, int resolution) {

        const int sampleRate = AUM_API_SAMPLE_RATE_88200;

        float amplitude = sampleRate / 4;

        int index;
        for (float i = 0; i < sampleRate; i++)
        {
            int index = (int)i;
            _Graphics.RawDataCacheEETZZ[index].x = -1 + (i / sampleRate) * resolution;
            _Graphics.RawDataCacheEETZZ[index].y = amplitude * this->oscillator.GetSinPoint(
                _Graphics.RawDataCacheEETZZ[index].x, frequency/2, sampleRate
            );
        }
        _Graphics.VertexBuffer = AUMOnoAPIGraphicsVertexBuffer(
            sizeof _Graphics.RawDataCacheEETZZ, _Graphics.RawDataCacheEETZZ
        );
        _Graphics.VertexBuffer.Bind();
    }

    /********************************************************************************************************/
        ////                         ////
        //// Wave function generator ////
        ////                         ////
        /////////////////////////////////

    void IAUMGraphicsSynthesizer::BindASineWave

        /* While running: */
        /* Use - or + to change the frequency, and q or e to change the resolution */

        (unsigned int shader, int xSectionCount, GLFWwindow* graphicalOutput, float frequency) {

        int sampleRate;

        switch (xSectionCount)
        {
        case 1:
            this->UseFFOZZSamplerateAndBufferTheWave(frequency, xSectionCount);
            break;
        case 2:
            this->UseEETZZSamplerateAndBufferTheWave(frequency, xSectionCount);
            break;
        }
    }

    int IAUMGraphicsSynthesizer::Run

        () {

        this->IsAvailable = true;
        this->IsRunning = true;

        if (this->IsAvailable)
        {

#ifdef AUM_WORKSTATION_RUN_CASE

            bool overrideToTest = false;
            int runCase = overrideToTest ? 0 : AUM_WORKSTATION_RUN_CASE;
            bool start = true;

            switch (runCase)
            {
                case 1:
                    if (this->IsRunning)
                    {
                        goto FunctionGeneratorRuntime;
                    }
                    else if (start){
                        this->IsRunning = true;
                    }
                FunctionGeneratorRuntime:
                    _AssertGL_(this->BindASineWave(
                        _Graphics.CurrentShader,
                        _Graphics.Resolution,
                        _Graphics.CurrentOutput,
                        _Graphics.Frequency
                    ));
                    return 1;
                    break;
                default:
                    break;
            }

#endif
        }
    }

}