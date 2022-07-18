#include "stdafx.h"
#include "VertexLine2Demo.h"

void VertexLine2Demo::Initialize()
{
	shader = new Shader(L"03_Pass.fxo");

	vertices[0].Position = Vector3(0, 0, 0);
	vertices[1].Position = Vector3(1, 0, 0);

	vertices[2].Position = Vector3(0, 0.5f, 0);
	vertices[3].Position = Vector3(1, 0.5f, 0);

	vertices[2].Position = Vector3(0, -0.5f, 0);
	vertices[3].Position = Vector3(1, -0.5f, 0);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 6;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
}

void VertexLine2Demo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void VertexLine2Demo::Update()
{
	
}

void VertexLine2Demo::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	shader->Draw(0, 0, 6);
}
//TODO. pass.fx �ۼ��ؾ� ��