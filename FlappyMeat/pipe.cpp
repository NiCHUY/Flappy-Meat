#include "pipe.h"

const int Pipe::kSpeed = 1;

Pipe::Pipe(QPoint center) : center_(center)
{

}

void Pipe::Update() {
    center_ -= QPoint{kSpeed, 0};
}

QPoint Pipe::GetPosition() {
    return center_;
}

void Pipe::SetPosition(QPoint pos) {
    center_ = pos;
}







