; ModuleID = './test/dfg/src/alg7.bc'
source_filename = "self_tests/src_huawei/alg7.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external hidden global i8
@llvm.global_ctors = appending global [1 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 65535, ptr @_GLOBAL__sub_I_alg7.cpp, ptr null }]

declare void @_ZNSt8ios_base4InitC1Ev(ptr noundef nonnull align 1 dereferenceable(1)) unnamed_addr #0

; Function Attrs: nounwind
declare void @_ZNSt8ios_base4InitD1Ev(ptr noundef nonnull align 1 dereferenceable(1)) unnamed_addr #1

; Function Attrs: nofree nounwind
declare i32 @__cxa_atexit(ptr, ptr, ptr) local_unnamed_addr #2

; Function Attrs: mustprogress nofree nosync nounwind memory(argmem: readwrite) uwtable
define dso_local void @_Z9alg7_funcPtS_(ptr nocapture noundef readonly %0, ptr nocapture noundef writeonly %1) local_unnamed_addr #3 {
  br label %4

3:                                                ; preds = %69
  ret void

4:                                                ; preds = %2, %69
  %5 = phi i32 [ 0, %2 ], [ %70, %69 ]
  %6 = phi i32 [ 0, %2 ], [ %10, %69 ]
  %7 = urem i32 %5, 2304
  %8 = icmp eq i32 %7, 0
  %9 = zext i1 %8 to i32
  %10 = add nuw nsw i32 %6, %9
  %11 = mul nuw nsw i32 %7, 887
  %12 = shl nsw i32 %10, 9
  %13 = add nuw nsw i32 %12, %11
  %14 = mul nsw i32 %10, 887
  %15 = shl nuw nsw i32 %7, 9
  %16 = sub nsw i32 %14, %15
  %17 = icmp sgt i32 %16, 1327103
  %18 = icmp ugt i32 %13, 2359295
  %19 = select i1 %18, i1 true, i1 %17
  %20 = icmp slt i32 %16, 0
  %21 = select i1 %19, i1 true, i1 %20
  br i1 %21, label %69, label %22

22:                                               ; preds = %4
  %23 = lshr i32 %16, 10
  %24 = lshr i32 %13, 10
  %25 = and i32 %16, 1023
  %26 = and i32 %13, 1023
  %27 = tail call i32 @llvm.smin.i32(i32 %24, i32 2302)
  %28 = add nuw nsw i32 %27, 1
  %29 = tail call i32 @llvm.smin.i32(i32 %23, i32 1294)
  %30 = mul nuw nsw i32 %23, 2304
  %31 = add nuw nsw i32 %30, %24
  %32 = getelementptr inbounds i16, ptr %0, i32 %31
  %33 = load i16, ptr %32, align 2, !tbaa !6
  %34 = add nuw nsw i32 %28, %30
  %35 = getelementptr inbounds i16, ptr %0, i32 %34
  %36 = load i16, ptr %35, align 2, !tbaa !6
  %37 = mul nuw nsw i32 %29, 2304
  %38 = add nuw nsw i32 %37, 2304
  %39 = add nuw nsw i32 %38, %24
  %40 = getelementptr inbounds i16, ptr %0, i32 %39
  %41 = load i16, ptr %40, align 2, !tbaa !6
  %42 = add nuw nsw i32 %38, %28
  %43 = getelementptr inbounds i16, ptr %0, i32 %42
  %44 = load i16, ptr %43, align 2, !tbaa !6
  %45 = zext i16 %33 to i32
  %46 = zext i16 %36 to i32
  %47 = sub nsw i32 %46, %45
  %48 = mul nsw i32 %47, %26
  %49 = lshr i32 %48, 10
  %50 = trunc i32 %49 to i16
  %51 = add i16 %33, %50
  %52 = zext i16 %41 to i32
  %53 = zext i16 %44 to i32
  %54 = sub nsw i32 %53, %52
  %55 = mul nsw i32 %54, %26
  %56 = lshr i32 %55, 10
  %57 = trunc i32 %56 to i16
  %58 = add i16 %41, %57
  %59 = zext i16 %51 to i32
  %60 = zext i16 %58 to i32
  %61 = sub nsw i32 %60, %59
  %62 = mul nsw i32 %61, %25
  %63 = lshr i32 %62, 10
  %64 = trunc i32 %63 to i16
  %65 = add i16 %51, %64
  %66 = mul nsw i32 %10, 2304
  %67 = add nuw nsw i32 %66, %7
  %68 = getelementptr inbounds i16, ptr %1, i32 %67
  store i16 %65, ptr %68, align 2, !tbaa !6
  br label %69

69:                                               ; preds = %4, %22
  %70 = add nuw nsw i32 %5, 1
  %71 = icmp eq i32 %70, 2985984
  br i1 %71, label %3, label %4, !llvm.loop !10
}

; Function Attrs: uwtable
define internal void @_GLOBAL__sub_I_alg7.cpp() #4 section ".text.startup" {
  tail call void @_ZNSt8ios_base4InitC1Ev(ptr noundef nonnull align 1 dereferenceable(1) @_ZStL8__ioinit)
  %1 = tail call i32 @__cxa_atexit(ptr nonnull @_ZNSt8ios_base4InitD1Ev, ptr nonnull @_ZStL8__ioinit, ptr nonnull @__dso_handle) #6
  ret void
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smin.i32(i32, i32) #5

attributes #0 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #2 = { nofree nounwind }
attributes #3 = { mustprogress nofree nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #4 = { uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #5 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!"Ubuntu clang version 16.0.6 (++20231112100421+7cbf1a259152-1~exp1~20231112100514.107)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"short", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = distinct !{!10, !11, !12}
!11 = !{!"llvm.loop.mustprogress"}
!12 = !{!"llvm.loop.unroll.disable"}
