//Written by Eric Dee.

#include "AUM-Ono-API-Graphics-Vertex-Buffer.h"

namespace AUM_Ono_API_Graphics {

	AUMOnoAPIGraphicsVertexBuffer::AUMOnoAPIGraphicsVertexBuffer
		()
	{
		this->phaseBufferId = 0;
	}

	AUMOnoAPIGraphicsVertexBuffer::AUMOnoAPIGraphicsVertexBuffer
		(unsigned int size, const void* plotPoints)
	{
		glGenBuffers(1, &this->phaseBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, this->phaseBufferId);
		glBufferData(GL_ARRAY_BUFFER, size, plotPoints, GL_STATIC_DRAW);
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