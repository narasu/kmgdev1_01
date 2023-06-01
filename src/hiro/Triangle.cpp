#include "Hiro.h"

namespace Hiro {
    Triangle::Triangle(Vector2<float> _pointA, Vector2<float> _pointB, Vector2<float> _pointC) {

        position = Vector2<float>((_pointA.x + _pointB.x + _pointC.x)/3, (_pointA.y + _pointB.y + _pointC.y)/3);
        Vector2<float> localPointA = _pointA - position;
        Vector2<float> localPointB = _pointB - position;
        Vector2<float> localPointC = _pointC - position;

        edges = std::vector<Edge> {
                Edge(*this, localPointA, localPointB),
                Edge(*this, localPointB, localPointC),
                Edge(*this, localPointC, localPointA)
        };

        std::cout << edges[0].projectionAxis() << edges[1].projectionAxis() << edges[2].projectionAxis() << std::endl;

        float a = (edges[1].projectionAxis().sqrMagnitude() + edges[2].projectionAxis().sqrMagnitude() - edges[0].projectionAxis().sqrMagnitude()) /
                (2 * edges[1].projectionAxis().magnitude() * edges[2].projectionAxis().magnitude());
        float b = (edges[0].projectionAxis().sqrMagnitude() + edges[2].projectionAxis().sqrMagnitude() - edges[1].projectionAxis().sqrMagnitude()) /
                (2 * edges[0].projectionAxis().magnitude() * edges[2].projectionAxis().magnitude());
        float c = (edges[0].projectionAxis().sqrMagnitude() + edges[1].projectionAxis().sqrMagnitude() - edges[2].projectionAxis().sqrMagnitude()) /
                (2 * edges[0].projectionAxis().magnitude() * edges[1].projectionAxis().magnitude());

        vertices[0] = Vertex(_pointA - position, a);
        vertices[1] = Vertex(_pointB - position, b);
        vertices[2] = Vertex(_pointC - position, c);

        std::vector<float> pointsX = std::vector<float> { _pointA.x, _pointB.x, _pointC.x };
        std::vector<float> pointsY = std::vector<float> { _pointA.y, _pointB.y, _pointC.y };

        Vector2<float> topLeft = Vector2<float>(*std::min_element(pointsX.begin(), pointsX.end()), *std::min_element(pointsY.begin(), pointsY.end()));
        Vector2<float> bottomRight = Vector2<float>(*std::max_element(pointsX.begin(), pointsX.end()), *std::max_element(pointsY.begin(), pointsY.end()));

        bounds = AABB<float>(topLeft, bottomRight);

        std::cout << "position: " << position << std::endl;
    }
}