// RUN: expt-opt %s | expt-opt | FileCheck %s

module {
    // CHECK-LABEL: func @bar()
    func.func @bar() {
        %0 = arith.constant 1 : i32
        // CHECK: %{{.*}} = Expt.foo %{{.*}} : i32
        %res = Expt.foo %0 : i32
        return
    }
}
