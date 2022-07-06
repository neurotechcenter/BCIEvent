#include "BCIEventApplication.hpp"


int main(){
    auto app = BCIEvent::BCIEventApplication();
    while (true){
	app.update(*app.currentSignal);
    }
    return 0;
}
