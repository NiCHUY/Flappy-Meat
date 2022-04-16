#include "pipe.h"

const int Pipe::kSpeed = 2;

Pipe::Pipe(QPoint center) : center_(center)
{

}

void Pipe::Update() {
    center_ -= QPoint{kSpeed, 0};
}

QPoint Pipe::GetPosition() {
    return center_;
}

bool Pipe::Inrtersects() {
    return false;
}

void Pipe::SetPosition(QPoint pos) {
    center_ = pos;
}
