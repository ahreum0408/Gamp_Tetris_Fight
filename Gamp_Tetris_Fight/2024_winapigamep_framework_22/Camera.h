#pragma once
class Camera
{
	DECLARE_SINGLE(Camera);
public:
	Vec2 GetCameraPos() { return m_camerapos; }
	void SetCameraPos(Vec2 _pos) { m_camerapos = _pos; }
private:
	Vec2 m_camerapos = { 0,0 };
};

