#include "BezierPath.h"

BezierPath::BezierPath()
{

}

BezierPath::~BezierPath()
{

}

//add curves to path
void BezierPath::AddCurve(BezierCurve curve, int samples)
{
    mCurves.push_back(curve);
    mSamples.push_back(samples);
}

//calculate samples and push in list
void BezierPath::Sample(std::vector<Vector2>* sampledPath)
{
    for (int i = 0; i < mCurves.size(); ++i)
    {
        for (float t = 0; t <= 1.0f; t += (1.0f / mSamples[i]))
        {
            sampledPath->push_back(mCurves[i].CalculateCurvePoint(t));
        }
    }
}