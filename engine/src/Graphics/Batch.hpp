#pragma once

template<typename TObject>
class Batch 
{
public:
	virtual ~Batch() 
	{
		delete m_NextBatch;
	}
	void AddObject(const TObject& object) 
	{
		if (IsOverflow()) 
		{
			if (!m_NextBatch)
				m_NextBatch = CreateNextBatch();
			m_NextBatch->AddObject(object);
			return;
		}
		AddObjectInternal(object);
	}
	void Render()  
	{
		RenderInternal();
		Reset();
		if (m_NextBatch)
			m_NextBatch->Render();
	}
protected:
	virtual void AddObjectInternal(const TObject&) = 0;
	virtual void RenderInternal() = 0;
	virtual Batch<TObject>* CreateNextBatch() const = 0;
	virtual void Reset() = 0;
	virtual bool IsOverflow() const = 0;
protected:
	Batch<TObject>* m_NextBatch = 0;
};