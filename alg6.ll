; ModuleID = './test/dfg/alg6.bc'
source_filename = "./self_tests/src_huawei/alg6.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

module asm ".globl _ZSt21ios_base_library_initv"

@d3_1 = dso_local local_unnamed_addr global [2985984 x i16] zeroinitializer, align 2
@d3_2 = dso_local local_unnamed_addr global [2985984 x i16] zeroinitializer, align 2
@d3_3 = dso_local local_unnamed_addr global [2985984 x i16] zeroinitializer, align 2
@d3_1_dst = dso_local local_unnamed_addr global [2985984 x i16] zeroinitializer, align 2
@d3_2_dst = dso_local local_unnamed_addr global [1492992 x i16] zeroinitializer, align 2
@d3_3_dst = dso_local local_unnamed_addr global [1492992 x i16] zeroinitializer, align 2

; Function Attrs: mustprogress nofree norecurse nosync nounwind uwtable
define dso_local void @_Z9alg6_funcPtS_PA2304_A3_t(ptr nocapture noundef writeonly %0, ptr nocapture noundef writeonly %1, ptr nocapture noundef readonly %2) local_unnamed_addr #0 {
  br label %4

4:                                                ; preds = %4, %3
  %5 = phi i32 [ 0, %3 ], [ %12, %4 ]
  %6 = phi i32 [ 0, %3 ], [ %35, %4 ]
  %7 = urem i32 %6, 2304
  %8 = icmp eq i32 %7, 0
  %9 = icmp ne i32 %6, 0
  %10 = and i1 %9, %8
  %11 = zext i1 %10 to i32
  %12 = add nuw nsw i32 %5, %11
  %13 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %12, i32 %7
  %14 = load i16, ptr %13, align 2, !tbaa !6
  %15 = zext i16 %14 to i32
  %16 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %12, i32 %7, i32 1
  %17 = load i16, ptr %16, align 2, !tbaa !6
  %18 = zext i16 %17 to i32
  %19 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %12, i32 %7, i32 2
  %20 = load i16, ptr %19, align 2, !tbaa !6
  %21 = zext i16 %20 to i32
  %22 = mul nuw nsw i32 %15, 38
  %23 = mul nuw nsw i32 %18, 75
  %24 = mul nuw nsw i32 %21, 15
  %25 = add nuw nsw i32 %22, 64
  %26 = add nuw nsw i32 %25, %23
  %27 = add nuw nsw i32 %26, %24
  %28 = lshr i32 %27, 7
  %29 = tail call i32 @llvm.umin.i32(i32 %28, i32 1023)
  %30 = trunc i32 %29 to i16
  %31 = mul nsw i32 %12, 2304
  %32 = add nuw nsw i32 %31, %7
  %33 = getelementptr inbounds [2985984 x i16], ptr @d3_1, i32 0, i32 %32
  store i16 %30, ptr %33, align 2, !tbaa !6
  %34 = getelementptr inbounds i16, ptr %1, i32 %32
  store i16 %30, ptr %34, align 2, !tbaa !6
  %35 = add nuw nsw i32 %6, 1
  %36 = icmp eq i32 %35, 2985984
  br i1 %36, label %37, label %4, !llvm.loop !10

37:                                               ; preds = %37, %4
  %38 = phi i32 [ %45, %37 ], [ 0, %4 ]
  %39 = phi i32 [ %69, %37 ], [ 0, %4 ]
  %40 = urem i32 %39, 2304
  %41 = icmp eq i32 %40, 0
  %42 = icmp ne i32 %39, 0
  %43 = and i1 %42, %41
  %44 = zext i1 %43 to i32
  %45 = add nuw nsw i32 %38, %44
  %46 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %45, i32 %40
  %47 = load i16, ptr %46, align 2, !tbaa !6
  %48 = zext i16 %47 to i32
  %49 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %45, i32 %40, i32 1
  %50 = load i16, ptr %49, align 2, !tbaa !6
  %51 = zext i16 %50 to i32
  %52 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %45, i32 %40, i32 2
  %53 = load i16, ptr %52, align 2, !tbaa !6
  %54 = zext i16 %53 to i32
  %55 = mul nsw i32 %48, -22
  %56 = mul nsw i32 %51, -42
  %57 = shl nuw nsw i32 %54, 6
  %58 = add nsw i32 %55, 64
  %59 = add nsw i32 %58, %56
  %60 = add nsw i32 %59, %57
  %61 = ashr i32 %60, 7
  %62 = tail call i32 @llvm.smin.i32(i32 %61, i32 511)
  %63 = tail call i32 @llvm.smax.i32(i32 %62, i32 -512)
  %64 = trunc i32 %63 to i16
  %65 = add nsw i16 %64, 512
  %66 = mul nsw i32 %45, 2304
  %67 = add nuw nsw i32 %66, %40
  %68 = getelementptr inbounds [2985984 x i16], ptr @d3_2, i32 0, i32 %67
  store i16 %65, ptr %68, align 2, !tbaa !6
  %69 = add nuw nsw i32 %39, 1
  %70 = icmp eq i32 %69, 2985984
  br i1 %70, label %95, label %37, !llvm.loop !13

71:                                               ; preds = %129, %71
  %72 = phi i32 [ %93, %71 ], [ 0, %129 ]
  %73 = phi i32 [ %79, %71 ], [ 0, %129 ]
  %74 = urem i32 %72, 2304
  %75 = icmp eq i32 %74, 0
  %76 = icmp ne i32 %72, 0
  %77 = and i1 %76, %75
  %78 = zext i1 %77 to i32
  %79 = add nuw nsw i32 %73, %78
  %80 = and i32 %74, 1
  %81 = icmp eq i32 %80, 0
  %82 = mul nsw i32 %79, 2304
  %83 = add nuw nsw i32 %82, %74
  %84 = mul nsw i32 %79, 1152
  %85 = lshr i32 %74, 1
  %86 = add nuw nsw i32 %84, %85
  %87 = select i1 %81, ptr @d3_2, ptr @d3_3
  %88 = select i1 %81, ptr @d3_2_dst, ptr @d3_3_dst
  %89 = getelementptr inbounds i16, ptr %87, i32 %83
  %90 = load i16, ptr %89, align 2, !tbaa !6
  %91 = tail call i16 @llvm.umin.i16(i16 %90, i16 1023)
  %92 = getelementptr inbounds i16, ptr %88, i32 %86
  store i16 %91, ptr %92, align 2, !tbaa !6
  %93 = add nuw nsw i32 %72, 1
  %94 = icmp eq i32 %93, 2985984
  br i1 %94, label %131, label %71, !llvm.loop !14

95:                                               ; preds = %95, %37
  %96 = phi i32 [ %103, %95 ], [ 0, %37 ]
  %97 = phi i32 [ %127, %95 ], [ 0, %37 ]
  %98 = urem i32 %97, 2304
  %99 = icmp eq i32 %98, 0
  %100 = icmp ne i32 %97, 0
  %101 = and i1 %100, %99
  %102 = zext i1 %101 to i32
  %103 = add nuw nsw i32 %96, %102
  %104 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %103, i32 %98
  %105 = load i16, ptr %104, align 2, !tbaa !6
  %106 = zext i16 %105 to i32
  %107 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %103, i32 %98, i32 1
  %108 = load i16, ptr %107, align 2, !tbaa !6
  %109 = zext i16 %108 to i32
  %110 = getelementptr inbounds [2304 x [3 x i16]], ptr %2, i32 %103, i32 %98, i32 2
  %111 = load i16, ptr %110, align 2, !tbaa !6
  %112 = zext i16 %111 to i32
  %113 = shl nuw nsw i32 %106, 6
  %114 = mul nsw i32 %109, -54
  %115 = mul nsw i32 %112, -10
  %116 = add nuw nsw i32 %113, 64
  %117 = add nsw i32 %116, %114
  %118 = add nsw i32 %117, %115
  %119 = ashr i32 %118, 7
  %120 = tail call i32 @llvm.smin.i32(i32 %119, i32 511)
  %121 = tail call i32 @llvm.smax.i32(i32 %120, i32 -512)
  %122 = trunc i32 %121 to i16
  %123 = add nsw i16 %122, 512
  %124 = mul nsw i32 %103, 2304
  %125 = add nuw nsw i32 %124, %98
  %126 = getelementptr inbounds [2985984 x i16], ptr @d3_3, i32 0, i32 %125
  store i16 %123, ptr %126, align 2, !tbaa !6
  %127 = add nuw nsw i32 %97, 1
  %128 = icmp eq i32 %127, 2985984
  br i1 %128, label %129, label %95, !llvm.loop !15

129:                                              ; preds = %95
  tail call void @llvm.memcpy.p0.p0.i32(ptr noundef nonnull align 2 dereferenceable(5971968) @d3_1_dst, ptr noundef nonnull align 2 dereferenceable(5971968) @d3_1, i32 5971968, i1 false), !tbaa !6
  br label %71

130:                                              ; preds = %148
  ret void

131:                                              ; preds = %148, %71
  %132 = phi i32 [ %152, %148 ], [ 0, %71 ]
  %133 = and i32 %132, 3
  switch i32 %133, label %144 [
    i32 0, label %134
    i32 1, label %137
    i32 2, label %141
  ]

134:                                              ; preds = %131
  %135 = lshr i32 %132, 2
  %136 = getelementptr inbounds [1492992 x i16], ptr @d3_2_dst, i32 0, i32 %135
  br label %148

137:                                              ; preds = %131
  %138 = add nsw i32 %132, -1
  %139 = lshr i32 %138, 1
  %140 = getelementptr inbounds [2985984 x i16], ptr @d3_1_dst, i32 0, i32 %139
  br label %148

141:                                              ; preds = %131
  %142 = lshr i32 %132, 2
  %143 = getelementptr inbounds [1492992 x i16], ptr @d3_3_dst, i32 0, i32 %142
  br label %148

144:                                              ; preds = %131
  %145 = add nsw i32 %132, -1
  %146 = lshr i32 %145, 1
  %147 = getelementptr inbounds [2985984 x i16], ptr @d3_1_dst, i32 0, i32 %146
  br label %148

148:                                              ; preds = %144, %141, %137, %134
  %149 = phi ptr [ %136, %134 ], [ %143, %141 ], [ %147, %144 ], [ %140, %137 ]
  %150 = load i16, ptr %149, align 2, !tbaa !6
  %151 = getelementptr inbounds i16, ptr %0, i32 %132
  store i16 %150, ptr %151, align 2, !tbaa !6
  %152 = add nuw nsw i32 %132, 1
  %153 = icmp eq i32 %152, 5971968
  br i1 %153, label %130, label %131, !llvm.loop !16
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smin.i32(i32, i32) #1

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smax.i32(i32, i32) #1

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umin.i32(i32, i32) #1

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i16 @llvm.umin.i16(i16, i16) #1

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i32(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i32, i1 immarg) #2

attributes #0 = { mustprogress nofree norecurse nosync nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 1}
!5 = !{!"clang version 16.0.6"}
!6 = !{!7, !7, i64 0}
!7 = !{!"short", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = distinct !{!10, !11, !12}
!11 = !{!"llvm.loop.mustprogress"}
!12 = !{!"llvm.loop.unroll.disable"}
!13 = distinct !{!13, !11, !12}
!14 = distinct !{!14, !11, !12}
!15 = distinct !{!15, !11, !12}
!16 = distinct !{!16, !11, !12}
