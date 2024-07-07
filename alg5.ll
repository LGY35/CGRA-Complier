; ModuleID = './test/dfg/src/alg5.bc'
source_filename = "self_tests/src_huawei/alg5.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@c1 = dso_local local_unnamed_addr global ptr null, align 4
@c2 = dso_local local_unnamed_addr global ptr null, align 4
@c3 = dso_local local_unnamed_addr global ptr null, align 4
@c4 = dso_local local_unnamed_addr global ptr null, align 4
@in_1 = dso_local local_unnamed_addr global ptr null, align 4
@in_2 = dso_local local_unnamed_addr global ptr null, align 4
@out = dso_local local_unnamed_addr global ptr null, align 4
@sum = dso_local local_unnamed_addr global i32 0, align 4

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @_Z9alg5_funcPA4608_sPA4608_A3_t(ptr nocapture noundef readonly %0, ptr nocapture noundef writeonly %1) local_unnamed_addr #0 {
  %3 = tail call noalias dereferenceable_or_null(5971968) ptr @malloc(i32 noundef 5971968) #2
  store ptr %3, ptr @c1, align 4, !tbaa !6
  %4 = tail call noalias dereferenceable_or_null(5971968) ptr @malloc(i32 noundef 5971968) #2
  store ptr %4, ptr @c2, align 4, !tbaa !6
  %5 = tail call noalias dereferenceable_or_null(5971968) ptr @malloc(i32 noundef 5971968) #2
  store ptr %5, ptr @c3, align 4, !tbaa !6
  %6 = tail call noalias dereferenceable_or_null(5971968) ptr @malloc(i32 noundef 5971968) #2
  store ptr %6, ptr @c4, align 4, !tbaa !6
  br label %7

7:                                                ; preds = %2, %32
  %8 = phi i32 [ 0, %2 ], [ %15, %32 ]
  %9 = phi i32 [ 0, %2 ], [ %33, %32 ]
  %10 = urem i32 %9, 4608
  %11 = icmp eq i32 %10, 0
  %12 = icmp ne i32 %9, 0
  %13 = and i1 %12, %11
  %14 = zext i1 %13 to i32
  %15 = add i32 %8, %14
  %16 = lshr i32 %15, 1
  %17 = lshr i32 %10, 1
  %18 = and i32 %15, 1
  %19 = icmp eq i32 %18, 0
  %20 = and i32 %10, 1
  %21 = icmp eq i32 %20, 0
  %22 = select i1 %19, i1 %21, i1 false
  br i1 %22, label %26, label %23

23:                                               ; preds = %7
  %24 = xor i1 %19, true
  %25 = select i1 %24, i1 true, i1 %21
  br i1 %25, label %32, label %26

26:                                               ; preds = %23, %7
  %27 = phi ptr [ %3, %7 ], [ %4, %23 ]
  %28 = getelementptr inbounds [4608 x i16], ptr %0, i32 %15, i32 %10
  %29 = load i16, ptr %28, align 2, !tbaa !10
  %30 = getelementptr inbounds [2304 x i16], ptr %27, i32 %16
  %31 = getelementptr inbounds i16, ptr %30, i32 %17
  store i16 %29, ptr %31, align 2, !tbaa !10
  br label %32

32:                                               ; preds = %26, %23
  %33 = add nuw nsw i32 %9, 1
  %34 = icmp eq i32 %33, 11943936
  br i1 %34, label %35, label %7, !llvm.loop !12

35:                                               ; preds = %32, %60
  %36 = phi i32 [ %43, %60 ], [ 0, %32 ]
  %37 = phi i32 [ %61, %60 ], [ 0, %32 ]
  %38 = urem i32 %37, 4608
  %39 = icmp eq i32 %38, 0
  %40 = icmp ne i32 %37, 0
  %41 = and i1 %40, %39
  %42 = zext i1 %41 to i32
  %43 = add i32 %36, %42
  %44 = lshr i32 %43, 1
  %45 = lshr i32 %38, 1
  %46 = and i32 %43, 1
  %47 = icmp eq i32 %46, 0
  %48 = xor i1 %47, true
  %49 = and i32 %38, 1
  %50 = icmp eq i32 %49, 0
  %51 = select i1 %48, i1 %50, i1 false
  br i1 %51, label %54, label %52

52:                                               ; preds = %35
  %53 = select i1 %47, i1 true, i1 %50
  br i1 %53, label %60, label %54

54:                                               ; preds = %52, %35
  %55 = phi ptr [ %5, %35 ], [ %6, %52 ]
  %56 = getelementptr inbounds [4608 x i16], ptr %0, i32 %43, i32 %38
  %57 = load i16, ptr %56, align 2, !tbaa !10
  %58 = getelementptr inbounds [2304 x i16], ptr %55, i32 %44
  %59 = getelementptr inbounds i16, ptr %58, i32 %45
  store i16 %57, ptr %59, align 2, !tbaa !10
  br label %60

60:                                               ; preds = %54, %52
  %61 = add nuw nsw i32 %37, 1
  %62 = icmp eq i32 %61, 11943936
  br i1 %62, label %63, label %35, !llvm.loop !15

63:                                               ; preds = %60, %100
  %64 = phi i32 [ %71, %100 ], [ 0, %60 ]
  %65 = phi i32 [ %101, %100 ], [ 0, %60 ]
  %66 = urem i32 %65, 4608
  %67 = icmp eq i32 %66, 0
  %68 = icmp ne i32 %65, 0
  %69 = and i1 %68, %67
  %70 = zext i1 %69 to i32
  %71 = add i32 %64, %70
  %72 = and i32 %71, 1
  %73 = icmp eq i32 %72, 0
  %74 = and i32 %66, 1
  %75 = icmp eq i32 %74, 0
  %76 = select i1 %73, i1 %75, i1 false
  br i1 %76, label %77, label %100

77:                                               ; preds = %63
  %78 = lshr i32 %66, 1
  %79 = lshr i32 %71, 1
  %80 = getelementptr inbounds [2304 x i16], ptr %3, i32 %79
  %81 = getelementptr inbounds i16, ptr %80, i32 %78
  %82 = load i16, ptr %81, align 2, !tbaa !10
  %83 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %71, i32 %66
  store i16 %82, ptr %83, align 2, !tbaa !10
  %84 = getelementptr inbounds [2304 x i16], ptr %4, i32 %79
  %85 = getelementptr inbounds i16, ptr %84, i32 %78
  %86 = load i16, ptr %85, align 2, !tbaa !10
  %87 = zext i16 %86 to i32
  %88 = getelementptr inbounds [2304 x i16], ptr %5, i32 %79
  %89 = getelementptr inbounds i16, ptr %88, i32 %78
  %90 = load i16, ptr %89, align 2, !tbaa !10
  %91 = zext i16 %90 to i32
  %92 = add nuw nsw i32 %91, %87
  %93 = lshr i32 %92, 1
  %94 = trunc i32 %93 to i16
  %95 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %71, i32 %66, i32 1
  store i16 %94, ptr %95, align 2, !tbaa !10
  %96 = getelementptr inbounds [2304 x i16], ptr %6, i32 %79
  %97 = getelementptr inbounds i16, ptr %96, i32 %78
  %98 = load i16, ptr %97, align 2, !tbaa !10
  %99 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %71, i32 %66, i32 2
  store i16 %98, ptr %99, align 2, !tbaa !10
  br label %100

100:                                              ; preds = %77, %63
  %101 = add nuw nsw i32 %65, 1
  %102 = icmp eq i32 %101, 11943936
  br i1 %102, label %103, label %63, !llvm.loop !16

103:                                              ; preds = %100, %132
  %104 = phi i32 [ %111, %132 ], [ 0, %100 ]
  %105 = phi i32 [ %133, %132 ], [ 0, %100 ]
  %106 = urem i32 %105, 4608
  %107 = icmp eq i32 %106, 0
  %108 = icmp ne i32 %105, 0
  %109 = and i1 %108, %107
  %110 = zext i1 %109 to i32
  %111 = add i32 %104, %110
  %112 = and i32 %111, 1
  %113 = icmp eq i32 %112, 0
  %114 = and i32 %106, 1
  %115 = icmp eq i32 %114, 0
  %116 = xor i1 %115, %113
  br i1 %116, label %117, label %132

117:                                              ; preds = %103
  %118 = lshr i32 %106, 1
  %119 = lshr i32 %111, 1
  %120 = getelementptr inbounds [2304 x i16], ptr %3, i32 %119
  %121 = getelementptr inbounds i16, ptr %120, i32 %118
  %122 = load i16, ptr %121, align 2, !tbaa !10
  %123 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %111, i32 %106
  store i16 %122, ptr %123, align 2, !tbaa !10
  %124 = getelementptr inbounds [2304 x i16], ptr %4, i32 %119
  %125 = getelementptr inbounds i16, ptr %124, i32 %118
  %126 = load i16, ptr %125, align 2, !tbaa !10
  %127 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %111, i32 %106, i32 1
  store i16 %126, ptr %127, align 2, !tbaa !10
  %128 = getelementptr inbounds [2304 x i16], ptr %5, i32 %119
  %129 = getelementptr inbounds i16, ptr %128, i32 %118
  %130 = load i16, ptr %129, align 2, !tbaa !10
  %131 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %111, i32 %106, i32 2
  store i16 %130, ptr %131, align 2, !tbaa !10
  br label %132

132:                                              ; preds = %103, %117
  %133 = add nuw nsw i32 %105, 1
  %134 = icmp eq i32 %133, 11943936
  br i1 %134, label %136, label %103, !llvm.loop !17

135:                                              ; preds = %173
  ret void

136:                                              ; preds = %132, %173
  %137 = phi i32 [ %144, %173 ], [ 0, %132 ]
  %138 = phi i32 [ %174, %173 ], [ 0, %132 ]
  %139 = urem i32 %138, 4608
  %140 = icmp eq i32 %139, 0
  %141 = icmp ne i32 %138, 0
  %142 = and i1 %141, %140
  %143 = zext i1 %142 to i32
  %144 = add i32 %137, %143
  %145 = and i32 %144, 1
  %146 = icmp eq i32 %145, 0
  %147 = and i32 %139, 1
  %148 = icmp eq i32 %147, 0
  %149 = select i1 %146, i1 true, i1 %148
  br i1 %149, label %173, label %150

150:                                              ; preds = %136
  %151 = lshr i32 %139, 1
  %152 = lshr i32 %144, 1
  %153 = getelementptr inbounds [2304 x i16], ptr %3, i32 %152
  %154 = getelementptr inbounds i16, ptr %153, i32 %151
  %155 = load i16, ptr %154, align 2, !tbaa !10
  %156 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %144, i32 %139
  store i16 %155, ptr %156, align 2, !tbaa !10
  %157 = getelementptr inbounds [2304 x i16], ptr %4, i32 %152
  %158 = getelementptr inbounds i16, ptr %157, i32 %151
  %159 = load i16, ptr %158, align 2, !tbaa !10
  %160 = zext i16 %159 to i32
  %161 = getelementptr inbounds [2304 x i16], ptr %5, i32 %152
  %162 = getelementptr inbounds i16, ptr %161, i32 %151
  %163 = load i16, ptr %162, align 2, !tbaa !10
  %164 = zext i16 %163 to i32
  %165 = add nuw nsw i32 %164, %160
  %166 = lshr i32 %165, 1
  %167 = trunc i32 %166 to i16
  %168 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %144, i32 %139, i32 1
  store i16 %167, ptr %168, align 2, !tbaa !10
  %169 = getelementptr inbounds [2304 x i16], ptr %6, i32 %152
  %170 = getelementptr inbounds i16, ptr %169, i32 %151
  %171 = load i16, ptr %170, align 2, !tbaa !10
  %172 = getelementptr inbounds [4608 x [3 x i16]], ptr %1, i32 %144, i32 %139, i32 2
  store i16 %171, ptr %172, align 2, !tbaa !10
  br label %173

173:                                              ; preds = %150, %136
  %174 = add nuw nsw i32 %138, 1
  %175 = icmp eq i32 %174, 11943936
  br i1 %175, label %135, label %136, !llvm.loop !18
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i32 noundef) local_unnamed_addr #1

attributes #0 = { mustprogress nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind allocsize(0) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!"Ubuntu clang version 16.0.6 (++20231112100421+7cbf1a259152-1~exp1~20231112100514.107)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"any pointer", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = !{!11, !11, i64 0}
!11 = !{!"short", !8, i64 0}
!12 = distinct !{!12, !13, !14}
!13 = !{!"llvm.loop.mustprogress"}
!14 = !{!"llvm.loop.unroll.disable"}
!15 = distinct !{!15, !13, !14}
!16 = distinct !{!16, !13, !14}
!17 = distinct !{!17, !13, !14}
!18 = distinct !{!18, !13, !14}
