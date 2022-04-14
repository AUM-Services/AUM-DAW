//Written by Eric Dee.

#include "AUM-Ono-API-Context-Graphics.h"

namespace AUM_Ono_API_Context_Graphics {

	AUMOnoAPIGraphicsUnitTest AUMOnoAPIContextGraphics::Catch = AUMOnoAPIGraphicsUnitTest();

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

}