//Written by Eric Dee.

#include "AUM-Ono-API-Graphics-Vertex-Buffer.h"

namespace AUM_Ono_API_Graphics {

	AUMOnoAPIGraphicsVertexBuffer::AUMOnoAPIGraphicsVertexBuffer
		()
	{
		// Initialize out of range for error checking.
		this->phaseBufferId = -128;
	}

	AUMOnoAPIGraphicsVertexBuffer::AUMOnoAPIGraphicsVertexBuffer
		(unsigned int size, const void* plotPoints)
	{
		glGenBuffers(1, &this->phaseBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, this->phaseBufferId);
		glBufferData(GL_ARRAY_BUFFER, size, plotPoints, GL_STATIC_DRAW);
		// GL static draw indicates this data won't be written to the buffer too often.
		// As such, GL stores a copy of the buffer in the GPU AM.
	}

	void AUMOnoAPIGraphicsVertexBuffer::Bind
		() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, phaseBufferId);
	}

	void AUMOnoAPIGraphicsVertexBuffer::Unbind
		() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const unsigned int* AUMOnoAPIGraphicsVertexBuffer::GetAddress
	() const
	{
		return &this->phaseBufferId;
	}

}