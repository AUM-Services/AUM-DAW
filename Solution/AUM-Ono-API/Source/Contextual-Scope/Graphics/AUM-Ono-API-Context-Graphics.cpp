//Written by Eric Dee.

#include "AUM-Ono-API-Context-Graphics.h"

namespace AUM_Ono_API_Context_Graphics {

    GLFWwindow* AUMOnoAPIContextGraphics::CurrentOutput;
    unsigned int AUMOnoAPIContextGraphics::CurrentShader;
    int AUMOnoAPIContextGraphics::Resolution;
    float AUMOnoAPIContextGraphics::Frequency;
    bool AUMOnoAPIContextGraphics::ResolutionShouldRebind;
    bool AUMOnoAPIContextGraphics::FrequencyShouldRebind;

    AUMOnoAPIContextGraphics::AUMOnoAPIContextGraphics
        
        () {
        this->CurrentOutput = nullptr;
        this->CurrentShader = 0;
        this->Resolution = 1;
        this->Frequency = 0.0f;
        this->ResolutionShouldRebind = false;
        this->FrequencyShouldRebind = false;
    }

/********************************************************************************************************/
    ////                                                                                        ////
    ////  This is a static singleton found in the AUM_Ono_API_Context_Graphics namespace. ////
    ////                                                                                        ////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    AUMOnoAPIContextGraphics::PlotAxisFFOZZ AUMOnoAPIContextGraphics::RawDataCacheFFOZZ[44100];
    AUMOnoAPIContextGraphics::PlotAxisEETZZ AUMOnoAPIContextGraphics::RawDataCacheEETZZ[88200];
	AUMOnoAPIGraphicsUnitTest AUMOnoAPIContextGraphics::Catch = AUMOnoAPIGraphicsUnitTest();
    AUMOnoAPIGraphicsVertexBuffer AUMOnoAPIContextGraphics::VertexBuffer = AUMOnoAPIGraphicsVertexBuffer();

	string AUMOnoAPIContextGraphics::GetError
		(int error)
	{
		return AUMOnoAPIContextGraphics::Catch.Errors.Map[error];
	}

	string AUMOnoAPIContextGraphics::GetErrorType
		(int error)
	{
		return AUMOnoAPIContextGraphics::Catch.ErrorTypes.Map[error];
	}

	void AUMOnoAPIContextGraphics::PrintInitilizationError
		(int error)
	{
		AUMWorkstationItemError(
			"{0} failed during {1}.",
			GetError(error),
			GetErrorType(Catch.ErrorTypes.INITIALIZATION)
		);
		
	}

	void AUMOnoAPIContextGraphics::PrintUpdateError
		(int error)
	{
		AUMWorkstationItemError(
			"{0} failed during {1}.",
			GetError(error),
			GetErrorType(Catch.ErrorTypes.UPDATE)
		);

	}

/********************************************************************************************************/
    ////                  ////
    //// GL error getters ////
    ////                  ////
    //////////////////////////

    /// <summary>
    /// Cleans out the error backlog from OpenGL.
    /// </summary>
    void AUMOnoAPIContextGraphics::CleanGLErrors
    ()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    /// <summary>
    /// Prints held errors while retrieving them from OpenGL.
    /// </summary>
    void AUMOnoAPIContextGraphics::GetGLErrors
    ()
    {
        while (GLenum error = glGetError())
        {
            AUMWorkstationItemError("OpenGL had this error: {0}", error);
        }
    }

    /// <summary>
    /// Wrapped/Decorated event that uses an assertion on gl error, and tells you the error location.
    /// </summary>
    /// <param name="file">The file name.</param>
    /// <param name="function">The function being called.</param>
    /// <param name="line">The line of code it is being called from.</param>
    /// <returns>Success or fail.</returns>
    bool AUMOnoAPIContextGraphics::ListenForGLErrorEvent
    (const char* file, const char* function, int line)
    {
        while (GLenum error = glGetError())
        {
            AUMWorkstationItemError(
                "OpenGL had this error: {0} from file {1}, calling function {2}, on line {3}",
                error, file, function, line
            );
            return false;
        }
        return true;
    }

}