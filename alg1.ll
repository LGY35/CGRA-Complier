; ModuleID = './test/dfg/src/alg1.bc'
source_filename = "self_tests/src_huawei/alg1.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external hidden global i8
@v1 = dso_local local_unnamed_addr global ptr null, align 4
@v2 = dso_local local_unnamed_addr global ptr null, align 4
@llvm.global_ctors = appending global [1 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 65535, ptr @_GLOBAL__sub_I_alg1.cpp, ptr null }]

declare void @_ZNSt8ios_base4InitC1Ev(ptr noundef nonnull align 1 dereferenceable(1)) unnamed_addr #0

; Function Attrs: nounwind
declare void @_ZNSt8ios_base4InitD1Ev(ptr noundef nonnull align 1 dereferenceable(1)) unnamed_addr #1

; Function Attrs: nofree nounwind
declare i32 @__cxa_atexit(ptr, ptr, ptr) local_unnamed_addr #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define dso_local void @_Z10alg1_func1PA2304_A3_tPA4608_S_(ptr nocapture noundef writeonly %0, ptr nocapture noundef readonly %1) local_unnamed_addr #3 {
  br label %4

3:                                                ; preds = %4
  ret void

4:                                                ; preds = %2, %4
  %5 = phi i32 [ 0, %2 ], [ %28, %4 ]
  %6 = phi i32 [ 0, %2 ], [ %12, %4 ]
  %7 = urem i32 %5, 2304
  %8 = icmp eq i32 %7, 0
  %9 = icmp ne i32 %5, 0
  %10 = and i1 %9, %8
  %11 = zext i1 %10 to i32
  %12 = add nuw nsw i32 %6, %11
  %13 = shl nuw nsw i32 %12, 1
  %14 = or i32 %13, 1
  %15 = icmp ugt i32 %14, 2591
  %16 = select i1 %15, i32 %13, i32 %14
  %17 = shl nuw nsw i32 %7, 1
  %18 = or i32 %17, 1
  %19 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %16, i32 %18
  %20 = load i16, ptr %19, align 2, !tbaa !6
  %21 = getelementptr inbounds [2304 x [3 x i16]], ptr %0, i32 %12, i32 %7
  store i16 %20, ptr %21, align 2, !tbaa !6
  %22 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %16, i32 %18, i32 1
  %23 = load i16, ptr %22, align 2, !tbaa !6
  %24 = getelementptr inbounds [2304 x [3 x i16]], ptr %0, i32 %12, i32 %7, i32 1
  store i16 %23, ptr %24, align 2, !tbaa !6
  %25 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %16, i32 %18, i32 2
  %26 = load i16, ptr %25, align 2, !tbaa !6
  %27 = getelementptr inbounds [2304 x [3 x i16]], ptr %0, i32 %12, i32 %7, i32 2
  store i16 %26, ptr %27, align 2, !tbaa !6
  %28 = add nuw nsw i32 %5, 1
  %29 = icmp eq i32 %28, 2985984
  br i1 %29, label %3, label %4, !llvm.loop !10
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @_Z10alg1_func2PiPt(ptr nocapture noundef %0, ptr nocapture noundef readonly %1) local_unnamed_addr #4 {
  %3 = tail call noalias dereferenceable_or_null(11943936) ptr @malloc(i32 noundef 11943936) #9
  store ptr %3, ptr @v1, align 4, !tbaa !13
  %4 = tail call noalias dereferenceable_or_null(11943936) ptr @malloc(i32 noundef 11943936) #9
  store ptr %4, ptr @v2, align 4, !tbaa !13
  br label %5

5:                                                ; preds = %2, %5
  %6 = phi i32 [ 0, %2 ], [ %13, %5 ]
  %7 = phi i32 [ 0, %2 ], [ %38, %5 ]
  %8 = urem i32 %7, 4608
  %9 = icmp eq i32 %8, 0
  %10 = icmp ne i32 %7, 0
  %11 = and i1 %10, %9
  %12 = zext i1 %11 to i32
  %13 = add i32 %6, %12
  %14 = mul i32 %13, 4608
  %15 = add i32 %14, %8
  %16 = shl i32 %15, 1
  %17 = getelementptr inbounds i16, ptr %1, i32 %16
  %18 = load i16, ptr %17, align 2, !tbaa !6
  %19 = zext i16 %18 to i32
  %20 = shl nuw nsw i32 %19, 10
  %21 = or i32 %16, 1
  %22 = getelementptr inbounds i16, ptr %1, i32 %21
  %23 = load i16, ptr %22, align 2, !tbaa !6
  %24 = zext i16 %23 to i32
  %25 = udiv i32 %20, %24
  %26 = tail call i32 @llvm.umin.i32(i32 %25, i32 4094)
  %27 = lshr exact i32 %14, 1
  %28 = add nuw i32 %27, %8
  %29 = getelementptr inbounds i32, ptr %3, i32 %28
  store i32 %26, ptr %29, align 4, !tbaa !15
  %30 = add i32 %16, 4609
  %31 = getelementptr inbounds i16, ptr %1, i32 %30
  %32 = load i16, ptr %31, align 2, !tbaa !6
  %33 = zext i16 %32 to i32
  %34 = shl nuw nsw i32 %33, 10
  %35 = udiv i32 %34, %24
  %36 = tail call i32 @llvm.umin.i32(i32 %35, i32 4094)
  %37 = getelementptr inbounds i32, ptr %4, i32 %28
  store i32 %36, ptr %37, align 4, !tbaa !15
  %38 = add nuw nsw i32 %7, 1
  %39 = icmp eq i32 %38, 11943936
  br i1 %39, label %40, label %5, !llvm.loop !17

40:                                               ; preds = %5
  tail call void @llvm.memset.p0.i32(ptr noundef nonnull align 4 dereferenceable(512) %0, i8 0, i32 512, i1 false), !tbaa !15
  br label %42

41:                                               ; preds = %42
  ret void

42:                                               ; preds = %40, %42
  %43 = phi i32 [ %69, %42 ], [ 0, %40 ]
  %44 = phi i32 [ %50, %42 ], [ 0, %40 ]
  %45 = urem i32 %43, 4608
  %46 = icmp eq i32 %45, 0
  %47 = icmp ne i32 %43, 0
  %48 = and i1 %47, %46
  %49 = zext i1 %48 to i32
  %50 = add i32 %44, %49
  %51 = mul i32 %50, 4608
  %52 = lshr exact i32 %51, 1
  %53 = add nuw i32 %52, %45
  %54 = getelementptr inbounds i32, ptr %3, i32 %53
  %55 = load i32, ptr %54, align 4, !tbaa !15
  %56 = sdiv i32 %55, 255
  %57 = getelementptr inbounds i32, ptr %4, i32 %53
  %58 = load i32, ptr %57, align 4, !tbaa !15
  %59 = sdiv i32 %58, 511
  %60 = tail call i32 @llvm.smin.i32(i32 %56, i32 7)
  %61 = tail call i32 @llvm.smax.i32(i32 %60, i32 0)
  %62 = tail call i32 @llvm.smin.i32(i32 %59, i32 15)
  %63 = tail call i32 @llvm.smax.i32(i32 %62, i32 0)
  %64 = shl nuw nsw i32 %61, 4
  %65 = add nuw nsw i32 %64, %63
  %66 = getelementptr inbounds i32, ptr %0, i32 %65
  %67 = load i32, ptr %66, align 4, !tbaa !15
  %68 = add nsw i32 %67, 1
  store i32 %68, ptr %66, align 4, !tbaa !15
  %69 = add nuw nsw i32 %43, 1
  %70 = icmp eq i32 %69, 11943936
  br i1 %70, label %41, label %42, !llvm.loop !18
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i32 noundef) local_unnamed_addr #5

; Function Attrs: uwtable
define internal void @_GLOBAL__sub_I_alg1.cpp() #6 section ".text.startup" {
  tail call void @_ZNSt8ios_base4InitC1Ev(ptr noundef nonnull align 1 dereferenceable(1) @_ZStL8__ioinit)
  %1 = tail call i32 @__cxa_atexit(ptr nonnull @_ZNSt8ios_base4InitD1Ev, ptr nonnull @_ZStL8__ioinit, ptr nonnull @__dso_handle) #10
  ret void
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smin.i32(i32, i32) #7

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smax.i32(i32, i32) #7

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umin.i32(i32, i32) #7

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i32(ptr nocapture writeonly, i8, i32, i1 immarg) #8

attributes #0 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #2 = { nofree nounwind }
attributes #3 = { mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #6 = { uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #7 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #8 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #9 = { nounwind allocsize(0) }
attributes #10 = { nounwind }

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
!13 = !{!14, !14, i64 0}
!14 = !{!"any pointer", !8, i64 0}
!15 = !{!16, !16, i64 0}
!16 = !{!"int", !8, i64 0}
!17 = distinct !{!17, !11, !12}
!18 = distinct !{!18, !11, !12}
