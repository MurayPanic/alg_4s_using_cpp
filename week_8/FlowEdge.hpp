#include<iostream>
#include<string>
#include<exception>
#include<cmath>

#ifndef FLOWEDGE_HPP
#define FLOWEDGE_HPP

//Class Declaration
class FlowEdge;

#endif

//Class Definition
class FlowEdge{
    public:
        FlowEdge();
        FlowEdge(int, int, double);
        FlowEdge(int, int, double, double);
        FlowEdge(const FlowEdge&);
        ~FlowEdge();

        void operator= (FlowEdge&);
        int from() const;
        int to() const;
        double capacity() const;
        double flow() const;
        int other(int);
        double residualCapacityTo(int); 
        void addResidualFlowTo(int, double);
        std::string toString();
    
    private:
        int v;
        int w;
        double capacity_val;
        double flow_val;

    

};

//Class definition
FlowEdge::FlowEdge(){}

FlowEdge::FlowEdge(int v, int w, double capacity_val){
    if(v<0 || w < 0){
        throw std::invalid_argument("vertex index must be a non-negative integer");
    }
    if (!(capacity_val >= 0.0)){
        throw  std::invalid_argument("Edge capacity must be non-negative");
    } 

    this->v = v;
    this->w = w;
    this->capacity_val = capacity_val;
    this->flow_val = 0.0;

    

}

FlowEdge::FlowEdge(int v, int w, double capacity_val, double flow_val){
    if(v<0 || w < 0){
        throw std::invalid_argument("vertex index must be a non-negative integer");
    }
    if (!(capacity_val >= 0.0)){
        throw  std::invalid_argument("Edge capacity must be non-negative");
    } 
    if(!(flow_val <= capacity_val)){
        throw std::invalid_argument("flow exceeds capacity");
    }
    if(!(flow_val>=0.0)){
        throw std::invalid_argument("flow must be non-negative");
    }

    this->v = v;
    this->w = w;
    this->capacity_val = capacity_val;
    this->flow_val = flow_val;

    

}

FlowEdge::FlowEdge(const FlowEdge& FE_ins){
    this->v = FE_ins.from();
    this->w = FE_ins.to();
    this->capacity_val = FE_ins.capacity();
    this->flow_val = FE_ins.flow();

}

FlowEdge::~FlowEdge(){}


//Member Function
void FlowEdge::operator=( FlowEdge& FE_ins){
        this->v = FE_ins.from();
        this->w = FE_ins.to();
        this->capacity_val = FE_ins.capacity();
        this->flow_val = FE_ins.flow();

}

int FlowEdge::from() const{
    return this->v;
}

int FlowEdge::to() const{
    return this->w;
}

double FlowEdge::capacity() const{
    return this->capacity_val;
}

double FlowEdge::flow() const{
    return this->flow_val;
}

int FlowEdge::other(int vertex){
    if(vertex == this->v){return this->w;      }
    else if(vertex == this->w){return this->v; }
    else {
        throw std::invalid_argument("invalid endpoint");
    }
}

double FlowEdge::residualCapacityTo(int vertex){
        if(vertex == this->v){return this->flow_val ;      }
    else if(vertex == this->w){return this->capacity_val - this->flow_val; }
    else {
        throw std::invalid_argument("invalid endpoint");
    }
}


void FlowEdge::addResidualFlowTo(int vertex, double delta){
    if(!(delta>=0.0) ){
        throw std::invalid_argument("Delta must be non-negative");
    }

    if (vertex == this->v){
        this->flow_val -= delta;
    }
    else if(vertex == this->w){
        this->flow_val += delta;
    }

    if(std::abs(this->flow_val) < 1E-10){
        this->flow_val = 0.0;

    }

    if(std::abs(this->flow_val - this->capacity_val) <= 1E-10){
        this->flow_val = this->capacity_val;
    }

    if(!(this->flow_val >=0) ){
        throw std::invalid_argument("Flow is negative");
    }

    if (!(this->flow_val <= this->capacity_val) ) {
        throw std::invalid_argument("Flow exceeds capacity");
    }


}

std::string FlowEdge::toString(){
    std::string FE_str = std::to_string(this->v) +
                        "->" + std::to_string(this->w) +
                        " " + std::to_string(this->flow_val)+
                       "/" +std::to_string(this->capacity_val);
    
    return FE_str;
}
