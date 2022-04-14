//Written by Eric Dee.

#include "GraphicsContext.h"

namespace AUMContext {

	GraphicsUnitTest GraphicsContext::Catch = GraphicsUnitTest();

	string GraphicsContext::GetError
		(int error)
	{
		return GraphicsContext::Catch.Errors.Map[error];
	}

	string GraphicsContext::GetErrorType
		(int error)
	{
		return GraphicsContext::Catch.ErrorTypes.Map[error];
	}

	void GraphicsContext::PrintInitilizationError
		(int error)
	{
		AUMAPIError(
			"{0} failed during {1}.",
			GetError(error),
			GetErrorType(Catch.ErrorTypes.INITIALIZATION)
		);
		
	}

	void GraphicsContext::PrintUpdateError
		(int error)
	{
		AUMAPIError(
			"{0} failed during {1}.",
			GetError(error),
			GetErrorType(Catch.ErrorTypes.UPDATE)
		);

	}

}